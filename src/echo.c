#include <stdlib.h>

#include "echo.h"


int echo_create_ctx(echo_ctx* _ctx) {
    if(!_ctx || !_ctx->info) return 0;

    _ctx->buffer = (char*) malloc(sizeof(char) * _ctx->info->len);
    if(!_ctx->buffer) return 0;

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
