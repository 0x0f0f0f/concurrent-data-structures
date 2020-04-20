/* Header file containing circular queue functions */
/* Need to define QUEUE_SIZE! */
#ifndef _BUF_H
#define _BUF_H

#define QUEUE_SIZE 4096

/* Buffer types, circular queue */
typedef struct __buf_t {
    void* buf[QUEUE_SIZE];
    int count;
    int head;
    int tail;
    char closed;
} buf_t;

/* Buffer utility macros and functions */
#define BUF_FULL(b) (b->count == QUEUE_SIZE)
#define BUF_EMPTY(b) (b->count == 0)
#define BUF_ASSERT_EXISTS(b) if(b == NULL) \
    {ERR_DIE("expected a buffer to be allocated: %p\n", (void*) b);}
#define BUF_OPEN(b) (b->closed == 0)
#define BUF_CLOSED(b) !BUF_OPEN(b)
#define BUF_CLOSE(b) (b->closed = 1)

/* Returns -1 on failure */
int buf_enqueue(buf_t* b, void* el);

/* Returns -1 on failure */
int buf_dequeue(buf_t* b, void** val);

/* Returns NULL on failure */
buf_t* buf_init();

void buf_destroy(buf_t *b);

#endif
