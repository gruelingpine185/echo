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

    _ctx->buffer = (char*) malloc(sizeof(char) * _ctx->info->len);
    if(!_ctx->buffer) return 0;

    memset(_ctx->buffer, 0, _ctx->info->len);
    if(setvbuf(_ctx->info->fs, _ctx->buffer, _IOFBF, _ctx->info->len) != 0) {
        echo_destroy_ctx(_ctx);
        return 0;
    }

    _ctx->offset = 0;
    _ctx->warnings = 0;
    _ctx->errors = 0;
    return 1;
}

void echo_destroy_ctx(echo_ctx* _ctx) {
    if(!_ctx || !_ctx->buffer) return;

    free(_ctx->buffer);
    _ctx->buffer = NULL;
}

void echo_log(echo_ctx* _ctx,
                echo_lvl _lvl,
                const char* _fname,
                int _ln,
                const char* _msg,
                ...) {
    int written = sprintf(_ctx->buffer + _ctx->offset,
                            "%s:%d: %s: ",
                            _fname,
                            _ln,
                            lvl_strs[_lvl]);
    _ctx->offset += written;
    va_list arg_list;
    va_start(arg_list, _msg);
    written = vsnprintf(_ctx->buffer + _ctx->offset,
                        _ctx->info->len,
                        _msg,
                        arg_list);
    va_end(arg_list);
    _ctx->offset += written;
    printf("%s\n", _ctx->buffer);
}
