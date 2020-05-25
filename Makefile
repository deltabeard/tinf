OPT ?= -Os
CFLAGS := -Isrc -Wall -Wextra -std=c89 -pedantic -g1 $(OPT)
all: examples/inflate
examples/inflate: examples/inflate.c src/tinflate.c src/tinf.h
