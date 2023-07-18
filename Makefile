lib_name := echo
lib_ext =
lib_full = $(bin_dir)/lib$(lib_name).$(lib_ext)

inc_dir := inc/$(lib_name)
src_dir := src
bin_dir := bin

headers := $(wildcard $(inc_dir)/*.h)
sources := $(wildcard $(src_dir)/*.c)
objects := $(patsubst $(src_dir)/%.c, $(bin_dir)/%.o, $(sources))

os := $(shell uname -s)
ifeq ($(os), Darwin)
	lib_ext = dylib
endif
ifeq ($(os), Linux)
	lib_ext = so
endif


c_std := -std=c11
c_opt := -O2
c_warn := -Wall -Wextra -pedantic
c_incs := -I$(inc_dir)
c_defs := -D_THREAD_SAFE
CC = clang
CFLAGS := $(c_std) $(c_opt) $(c_warn) $(c_defs)
LDLIBS := -lpthread


.PHONY: all clean
all:
	@$(MAKE) $(lib_full)
clean:
	rm -rf $(wildcard $(bin_dir) *.$(lib_ext) *.o)


$(lib_full): $(headers) $(sources) $(objects)
	$(CC) $(CFLAGS) $(c_incs) -shared $(objects) -o $@ $(LDLIBS)

$(bin_dir)/%.o: $(src_dir)/%.c $(bin_dir)
	$(CC) $(CFLAGS) $(c_incs) -fPIC -c $< -o $@

$(bin_dir):
	-mkdir $@
