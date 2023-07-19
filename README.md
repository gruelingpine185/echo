<div align="center">
    <img src="./assets/logo.svg" width="300px">
    <p>A thread-safe logging library for C and C++ projects.</p>
</div>

## Example

```c
#include <stdio.h>

#include <echo/echo.h>


int main(void) {
    // Create a output destination
    FILE* file = fopen("echo.log", "w");
    if(!file) return 1;

    // Setup information about the buffer and thread-safe-ness
    echo_info info = {0};
    info.fs = file;
    info.len = 1024;
    info.threshold = .9;
    info.is_thread_safe = 1;

    // Setup echo context
    echo_ctx ctx = {0};
    ctx.info = &info;

    // Create the buffer and other internals
    if(!echo_create_ctx(&ctx)) return 1;

    // Write your log messages
    ECHO_INFO("Hello world from Echo!");
    ECHO_DEBUG("Should have gotten an \'ECHO... Echo... echo...\'");
    ECHO_WARN("No echo yet?");
    ECHO_ERROR("Error[%d]: Echo is not echoing.", 32);

    // Don't forget to return resources
    echo_destroy_ctx(&ctx);
    fclose(file);
    return 0;
}
```
