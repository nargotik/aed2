CC=gcc
CFLAGS=-O3 -g3 -lm  -W -Wall -Wextra -Wuninitialized -Wstrict-aliasing -Wno-format-security -Wno-unused-but-set-variable -Wno-unused-rresult -std=c99 -Wno-unknown-pragmas
# Define as dependencias
DEPS = $(wildcard *.h)
# Define os ficheiros c a incluir
OBJ = $(wildcard *.c)

#.SILENT: all
%.o: %.c $(DEPS)
        $(CC) -c -o $@ $< $(CFLAGS)

all:
        $(CC) -o ../../bin/$(shell basename $(CURDIR)) *.c ../shared/*.c  $(CFLAGS);\
        EXIT_CODE=$$?;\
        echo "Compiler exited with $$EXIT_CODE";\
        exit $$EXIT_CODE

clean:
        rm bin/aed2
