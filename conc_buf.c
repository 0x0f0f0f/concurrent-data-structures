#include <stdio.h>
#include <conc_buf.h>
#include <logger.h>
#include <stdlib.h>
#include <buf.h>

#define MUTEX_LOCK_RET(m) \
    if((err = pthread_mutex_lock(m)) != 0) {\
        LOG_CRITICAL("error locking mutex %p\n", (void*) m);\
        return err;}

#define MUTEX_UNLOCK_RET(m) \
    if((err = pthread_mutex_unlock(m)) != 0) {\
        LOG_CRITICAL("error unlocking mutex %p\n", (void*) m);\
        return err;}

#define COND_SIGNAL_RET(e) \
    if((err = pthread_cond_signal(e)) != 0) {\
        LOG_CRITICAL("error signaling condition %p\n", (void*) e);\
        return err;}

#define COND_WAIT_RET(e, m) \
    if((err = pthread_cond_wait(e, m)) != 0) {\
        LOG_CRITICAL("error waiting condition %p\n", (void*) e);\
        return err;}



int conc_buf_enqueue(conc_buf_t* cb, void* val) {
    int err = 0;
    MUTEX_LOCK_RET(cb->mutex);
    while(buf_enqueue(cb->buf, val) == 1) {
        /* Buf is full, wait for consume event */
        LOG_DEBUG("waiting for space in buf %p", (void*) cb);
        COND_WAIT_RET(cb->consume_event, cb->mutex);
    }
    LOG_DEBUG("successfuly put element %p", (void*) val);
    COND_SIGNAL_RET(cb->produce_event);
    MUTEX_UNLOCK_RET(cb->mutex);
    return err;
}

int conc_buf_dequeue(conc_buf_t* cb, void** val) {
    int err = 0;
    MUTEX_LOCK_RET(cb->mutex);
    while((err = buf_dequeue(cb->buf, val)) == -1) {
        /* Buffer is empty, wait for value or check if closed */
        if(BUF_CLOSED(cb->buf)) {
            LOG_DEBUG("buf %p was closed\n", (void*) cb);
            MUTEX_UNLOCK_RET(cb->mutex);
            return EBUFCLOSED;
        }
        /* Otherwise wait for signal */
        COND_WAIT_RET(cb->produce_event, cb->mutex);
    }

    /* An item was consumed */
    COND_SIGNAL_RET(cb->consume_event);
    LOG_DEBUG("successfully popped element %p\n", *val);
    MUTEX_UNLOCK_RET(cb->mutex);
    return err;
}

int conc_buf_close(conc_buf_t* cb) {
    int err = 0;
    MUTEX_LOCK_RET(cb->mutex);
    BUF_CLOSE(cb->buf);
    COND_SIGNAL_RET(cb->produce_event);
    MUTEX_UNLOCK_RET(cb->mutex);
    return err;
}

conc_buf_t* conc_buf_init() {
    conc_buf_t* cb = malloc(sizeof(conc_buf_t));
    if(cb == NULL) return cb;
    cb->buf = buf_init();
    if(cb->buf == NULL) return NULL;

    cb->mutex = malloc(sizeof(pthread_mutex_t));
    cb->consume_event = malloc(sizeof(pthread_cond_t));
    cb->produce_event = malloc(sizeof(pthread_cond_t));
    pthread_mutex_init(cb->mutex, NULL);
    pthread_cond_init(cb->consume_event, NULL);
    pthread_cond_init(cb->produce_event, NULL);

    return cb;
}

void conc_buf_destroy(conc_buf_t* cb) {
    if (cb == NULL) return;
    if(cb->mutex) pthread_mutex_destroy(cb->mutex);
    if(cb->consume_event) pthread_cond_destroy(cb->consume_event);
    if(cb->produce_event) pthread_cond_destroy(cb->produce_event);
    free(cb->mutex);
    free(cb->consume_event);
    free(cb->produce_event);
    buf_destroy(cb->buf);
    free(cb);
    return;
}
