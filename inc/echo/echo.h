#ifndef ECHO_ECHO_H
#define ECHO_ECHO_H


#include <stdint.h>
#include <stdio.h>
#include <pthread.h>


#ifdef ECHO_DISABLED
    #define ECHO_DISABLE_DEBUG
    #define ECHO_DISABLE_INFO
    #define ECHO_DISABLE_WARN
    #define ECHO_DISABLE_ERROR
    #define ECHO_DISABLE_FATAL
#endif // ECHO_DISABLED


#ifdef ECHO_DISABLE_DEBUG
    #define ECHO_DEBUG(_ctx_ptr, ...)
#else
    #define ECHO_DEBUG(_ctx_ptr, ...)                                       \
        echo_log(_ctx_ptr, ECHO_LVL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#endif // ECHO_DISABLE_DEBUG

#ifdef ECHO_DISABLE_INFO
    #define ECHO_DEBUG(_ctx_ptr, ...)
#else
    #define ECHO_INFO(_ctx_ptr, ...)                                        \
        echo_log(_ctx_ptr, ECHO_LVL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#endif // ECHO_DISABLE_INFO

#ifdef ECHO_DISABLE_WARN
    #define ECHO_WARN(_ctx_ptr, ...)
#else
    #define ECHO_WARN(_ctx_ptr, ...)                                        \
        echo_log(_ctx_ptr, ECHO_LVL_WARN, __FILE__, __LINE__, __VA_ARGS__)
#endif // ECHO_DISABLE_WARN

#ifdef ECHO_DISABLE_ERROR
    #define ECHO_ERROR(_ctx_ptr, ...)
#else
    #define ECHO_ERROR(_ctx_ptr, ...)                                       \
        echo_log(_ctx_ptr, ECHO_LVL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#endif // ECHO_DISABLE_ERROR

#ifdef ECHO_DISABLE_FATAL
    #define ECHO_FATAL(_ctx_ptr, ...)
#else
    #define ECHO_FATAL(_ctx_ptr, ...)                                       \
        echo_log(_ctx_ptr, ECHO_LVL_FATAL, __FILE__, __LINE__, __VA_ARGS__)
#endif // ECHO_DISABLE_FATAL


typedef struct echo_ctx echo_ctx;
typedef struct echo_info echo_info;


typedef enum {
    ECHO_LVL_DEBUG,
    ECHO_LVL_INFO,
    ECHO_LVL_WARN,
    ECHO_LVL_ERROR,
    ECHO_LVL_FATAL
} echo_lvl;


struct echo_info {
    FILE* fs;
    uint32_t len;
    float threshold;
    int is_thread_safe;
    pthread_mutex_t lock;
};

struct echo_ctx {
    echo_info* info;
    char* buffer;
    uint32_t offset;
};


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
int echo_create_ctx(echo_ctx* _ctx);
void echo_destroy_ctx(echo_ctx* _ctx);
void echo_log(echo_ctx* _ctx,
                echo_lvl _lvl,
                const char* _fname,
                int _ln,
                const char* _msg,
                ...);
void echo_flush(echo_ctx* _ctx);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ECHO_ECHO_H
