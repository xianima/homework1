ver = debug

ifeq ($(ver),debug)
ccflags = -c -g 
else
ccflags = -c
endif

cc = gcc
prom = main
deps = $(shell find ./ -name "*.h")
srcs = $(shell find ./ -name "*.c")
objs = $(srcs:%.c=%.o)

$(prom): $(objs)
	$(cc) -o $(prom) $(objs)

%.o: %.c $(deps)
	$(cc) $(ccflags) $< -o $@

clean:
	rm -rf $(objs) $(prom)
