#ifndef _CONC_BUF_H
#define _CONC_BUF_H

#include <pthread.h>
#include <buf.h>

typedef struct __conc_buf {
    pthread_mutex_t* mutex;
    pthread_cond_t* produce_event;
    pthread_cond_t* consume_event;
    buf_t* buf;
} conc_buf_t;

/* Error code for closed buffer */
#define EBUFCLOSED -666

#define CONC_BUF_ASSERT_EXISTS(b) if(b == NULL) \
    {ERR_DIE("expected a buffer to be allocated: %p\n", (void*) b);}


/* Put an item in the buffer, doing appropriate locking and signaling */
int conc_buf_enqueue(conc_buf_t* cb, void* val);

/* Get an item from the buffer doing appropriate locking and signaling */
int conc_buf_dequeue(conc_buf_t* cb, void** val);

/* Close a concurrent buffer */
int conc_buf_close(conc_buf_t* cb);

/* Returns NULL on failure */
conc_buf_t* conc_buf_init();

void conc_buf_destroy(conc_buf_t* cb);

#endif
