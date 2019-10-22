CC=gcc
CFLAGS=-O3 -g3  -W -Wall -Wextra -Wunused-function -Wuninitialized -Wstrict-aliasing -Wno-format-security -Wno-unused-but-set-variable -Wno-unused-result -lsqlite3
# Define as dependencias
DEPS = $(wildcard *.h)
# Define os ficheiros c a incluir
OBJ = $(wildcard *.c)

all: clean
	$(CC) -o ../../bin/$(shell basename $(CURDIR)) main.c $(CFLAGS)


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	

clean:
	rm -f bin/display

