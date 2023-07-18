#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "echo.h"


const char* lvl_strs[5] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};


int echo_create_ctx(echo_ctx* _ctx) {
    if(!_ctx || !_ctx->info) return 0;
    if(_ctx->info->len < BUFSIZ) return 0;
    if(_ctx->info->is_thread_safe) {
        if(pthread_mutex_init(&_ctx->info->lock, NULL) != 0) return 0;
    }

    _ctx->buffer = (char*) malloc(sizeof(char) * _ctx->info->len);
    if(!_ctx->buffer) return 0;

    memset(_ctx->buffer, 0, _ctx->info->len);
    _ctx->offset = 0;
    return 1;
}

void echo_destroy_ctx(echo_ctx* _ctx) {
    if(!_ctx || !_ctx->buffer) return;
    if(_ctx->info->is_thread_safe) pthread_mutex_destroy(&_ctx->info->lock);

    echo_flush(_ctx);
    free(_ctx->buffer);
    _ctx->buffer = NULL;
}

void echo_log(echo_ctx* _ctx,
                echo_lvl _lvl,
                const char* _fname,
                int _ln,
                const char* _msg,
                ...) {
    if(_ctx->offset >= (_ctx->info->threshold * _ctx->info->len)) {
        echo_flush(_ctx);
    }

    if(_ctx->info->is_thread_safe) pthread_mutex_lock(&_ctx->info->lock);
    int written = sprintf(_ctx->buffer + _ctx->offset,
                            "%s:%d [%s]: ",
                            _fname,
                            _ln,
                            lvl_strs[_lvl]);
    _ctx->offset += written;
    va_list arg_list;
    va_start(arg_list, _msg);
    written = vsnprintf(_ctx->buffer + _ctx->offset,
                        (_ctx->info->len - _ctx->offset - 1),
                        _msg,
                        arg_list);
    _ctx->offset += written;
    strncat(_ctx->buffer, "\n", _ctx->info->len - _ctx->offset - 1);
    va_end(arg_list);
    _ctx->offset++;
    if(_ctx->info->is_thread_safe) pthread_mutex_unlock(&_ctx->info->lock);
}

void echo_flush(echo_ctx* _ctx) {
    if(_ctx->info->is_thread_safe) pthread_mutex_lock(&_ctx->info->lock);

    fprintf(_ctx->info->fs, "%s", _ctx->buffer);
    fflush(_ctx->info->fs);
    memset(_ctx->buffer, 0, _ctx->info->len);
    _ctx->offset = 0;
    if(_ctx->info->is_thread_safe) pthread_mutex_unlock(&_ctx->info->lock);
}
