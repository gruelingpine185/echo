#ifndef ECHO_ECHO_H
#define ECHO_ECHO_H


#include <stdint.h>
#include <stdio.h>


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
};

struct echo_ctx {
    echo_info* info;
    char* buffer;
    uint32_t offset;
    uint32_t warnings;
    uint32_t errors;
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
