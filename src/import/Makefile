CC=gcc
CFLAGS=-O3 -g3  -W -Wall -Wextra -Wuninitialized -Wstrict-aliasing -Wno-format-security -Wno-unused-but-set-variable -Wno-unused-result -lsqlite3 -lfl
# Define as dependencias
DEPS = $(wildcard *.h)
# Define os ficheiros c a incluir
OBJ = $(wildcard *.c)

all: clean flex_generated.c
	$(CC) -o ../../bin/$(shell basename $(CURDIR)) main.c flex_generated.c $(CFLAGS)
	rm flex_generated.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
flex_generated.c:
	flex -ll -t main.l > flex_generated.c
	#flex  -ll -t main.l > flex_generated.c
	
clean:
	rm -f bin/build
	rm -f flex_generated.c

