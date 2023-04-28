cc = gcc
flags = -Wall -Wextra -g
flags_release = -Wall -Wextra -O3 -flto
flags_link = -flto
main = main.c
src_dir = ./src
obj_dir = ./obj
exe = a.out
include_dir = $(src_dir)
headers = $(wildcard $(src_dir)/*.h)
src = $(wildcard $(src_dir)/*.c) $(main)
obj = $(addprefix $(obj_dir)/,$(subst .c,.o,$(notdir $(src))))

VPATH = ./src

all: $(dir) $(exe)

release: flags := $(flags_release)
release: re

$(exe) : $(obj)
	$(cc) $(flags) $^ -o $@

$(obj_dir)/%.o : %.c $(headers)
	$(cc) $(flags) -I $(include_dir) -c $< -o $@

dir:
	mkdir -p $(obj_dir)

clean:
	rm -f $(obj)

rm_exe:
	rm -f $(exe)

re: clean rm_exe all