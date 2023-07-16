#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "echo.h"


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
