/* Utility macros */
#ifndef UTIL_H
#define UTIL_H

/* Print to stderr */
#define ERR(...) fprintf(stderr, __VA_ARGS__);

/* Print an error and die */
#define ERR_DIE(...) ERR(__VA_ARGS__);\
    exit(EXIT_FAILURE);

/* Lock a mutex */
#define MUTEX_LOCK(mtx) \
    { int err = 0; if((err = pthread_mutex_lock(mtx)) != 0) {\
        ERR("error locking resource: %s\n", strerror(err)); pthread_exit((void*)&err);\
    } LOG_DEBUG("MUTEX %p locked\n", (void*)mtx);}

/* Unlock a mutex */
#define MUTEX_UNLOCK(mtx) \
    { int err = 0; if((err = pthread_mutex_unlock(mtx)) != 0) {\
        ERR("error unlocking resource: %s\n", strerror(err)); pthread_exit((void*)&err);\
    } LOG_DEBUG("MUTEX %p unlocked\n", (void*)mtx); }

/* Send a signal to a cond variable */
#define COND_SIGNAL(ev) \
    { int err = 0; if((err = pthread_cond_signal(ev)) != 0) {\
        ERR("error signaling cond: %s\n", strerror(err)); pthread_exit((void*)&err);\
    } /* printf("unlocked\n"); */ }

/* Send a signal to a cond variable */
#define COND_WAIT(event, mtx) \
    { int err = 0; if((err = pthread_cond_wait(event, mtx)) != 0) {\
        ERR("error waiting for cond: %s\n", strerror(err)); pthread_exit((void*)&err);\
    } /* printf("unlocked\n"); */ }


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


#define COND_BROADCAST_RET(e) \
    if((err = pthread_cond_signal(e)) != 0) {\
        LOG_CRITICAL("error broadcasting condition %p\n", (void*) e);\
        return err;}


#define COND_WAIT_RET(e, m) \
    if((err = pthread_cond_wait(e, m)) != 0) {\
        LOG_CRITICAL("error waiting condition %p\n", (void*) e);\
        return err;}

#endif
