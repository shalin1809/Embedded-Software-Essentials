
CC = gcc

CFLAGS = -c -Wall -g

options_c = hw1.c main.c hw1.h
options_o = hw1.o main.o

all: test

test : $(options_o)
	$(CC) $(options_o) -o test


# These are the preprocessed output .i files

preprocess : $(options_c)
	$(CC) $(options_c) -E > file.i

hw1.i : hw1.c
	$(CC) hw1.c -E > hw1.i

main.i : main.c
	$(CC) main.c -E > main.i


# These are the assembly output .S files

asm-file : $(options_c)
	$(CC) $(options_c) -S 

hw1.S : hw1.c hw1.h
	$(CC) hw1.c -S

main.S : main.c hw1.h
	$(CC) main.c -S


# Compiling (but not linking) the source code files

compile-all : $(options_c)
	$(CC) $(options_c) $(CFLAGS)

hw1.o : hw1.c hw1.h
	$(CC) hw1.c $(CFLAGS)

main.o : main.c hw1.h
	$(CC) main.c $(CFLAGS)


# Build - compiling and linking

build : $(options_c)
	$(CC) hw1.c $(CFLAGS)
	$(CC) main.c $(CFLAGS)
	$(CC) -o test $(options_o)



# Phony targets
.PHONY : clean
clean:
	rm -rf *.o *.map *.i *.s test

