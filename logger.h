#ifndef LOGGER_H
#define LOGGER_H

#include <pthread.h>
#include <stdarg.h>

enum loglevel {
	LOG_LVL_CRITICAL, // 0
	LOG_LVL_WARNING, // 1
	LOG_LVL_NOTICE, // 2
	LOG_LVL_DEBUG, // 3
};

static char* logname(enum loglevel l) {
    static char* strings[] = { "CRITICAL", "WARNING", "NOTICE", "DEBUG" };
    return strings[l];
}

#ifndef LOG_LVL
#define LOG_LVL LOG_LVL_NOTICE
#endif

#ifndef LOGFILE
#define LOGFILE stderr
#endif


#define LOG(level, fmt, args...) { if(level <= LOG_LVL) {\
    fprintf(LOGFILE, "[ %s - %s():%d ] "fmt, logname(level), __func__, __LINE__, ##args);\
	fflush(stderr); }}


#define LOG_CRITICAL(args...) LOG(LOG_LVL_CRITICAL, args)
#define LOG_WARNING(args...) LOG(LOG_LVL_WARNING, args)
#define LOG_NOTICE(args...) LOG(LOG_LVL_NOTICE, args)
#define LOG_DEBUG(args...) LOG(LOG_LVL_DEBUG, args)

#endif

