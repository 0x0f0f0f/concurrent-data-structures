#include <buf.h>
#include <logger.h>
#include <stdlib.h>
#include <stdio.h>

/* Returns -1 on failure */
int buf_enqueue(buf_t* b, void* el) {
    if(BUF_CLOSED(b)) {
        LOG_DEBUG("buffer %p was closed in enqueue", (void*) b);
        return -2;
    }
    if(BUF_FULL(b)) {
        LOG_DEBUG("buf %p is full in enqueue\n", (void*)b);
        return -1;
    }
    b->count++;
    b->buf[b->tail] = el;
    b->tail = (b->tail + 1) % QUEUE_SIZE;
    return 0;
}

/* Returns -1 on failure */
int buf_dequeue(buf_t* b, void** val) {
    if(BUF_EMPTY(b)) {
        LOG_DEBUG("buf %p is empty in dequeue\n", (void*)b);
        return -1;
    }
    *val = b->buf[b->head];
    b->head = (b->head + 1) % QUEUE_SIZE;
    b->count--;
    return 0;
}

/* Returns NULL on failure */
buf_t* buf_init() {
    buf_t *b = malloc(sizeof(buf_t));
    if (b == NULL) return b;
    b->count = 0;
    b->tail = 0;
    b->head = 0;
    b->closed = 0;
    for(int i = 0; i < QUEUE_SIZE; i++) b->buf[i] = NULL;
    return b;
}

void buf_destroy(buf_t *b) {
    for(int i = 0; i < QUEUE_SIZE; i++) free(b->buf[i]);
    free(b);
    return;
}
