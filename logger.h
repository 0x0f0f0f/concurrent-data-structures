#ifndef LOGGER_H
#define LOGGER_H

#include <pthread.h>

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

#define LOG(level, ...) { if(level <= LOG_LVL) {\
    fprintf(LOGFILE, "[ %s ]: ", logname(level));\
	fflush(stderr);\
	fprintf(LOGFILE, __VA_ARGS__); fflush(stderr); }}


#define LOG_CRITICAL(...) LOG(LOG_LVL_CRITICAL, __VA_ARGS__)
#define LOG_WARNING(...) LOG(LOG_LVL_WARNING, __VA_ARGS__)
#define LOG_NOTICE(...) LOG(LOG_LVL_NOTICE, __VA_ARGS__)
#define LOG_DEBUG(...) LOG(LOG_LVL_DEBUG, __VA_ARGS__)

#endif

