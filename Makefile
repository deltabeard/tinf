CFLAGS := -I src -Wall
all: examples/inflate
examples/inflate: examples/inflate.c src/tinflate.c
