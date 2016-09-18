
CC = gcc

CFLAGS = -c -Wall -g -std=c99 -O0

options_c = data.c memory.c main.c project_1.c data.h memory.h project_1.h
options_o = data.o memory.o project_1.o main.o

all: project

project : $(options_o)
	$(CC) $(options_o) -o project


# These are the preprocessed output .i files

preprocess : $(options_c)
	$(CC) $(options_c) -E > file.i

data.i : data.c
	$(CC) data.c -E > data.i

memory.i : memory.c
	$(CC) memory.c -E > memory.i

project_1.i : project_1.c
	$(CC) project_1.c -E > project_1.i

main.i : main.c
	$(CC) main.c -E > main.i


# These are the assembly output .S files

asm-file : $(options_c)
	$(CC) $(options_c) -S 

data.S : data.c data.h
	$(CC) data.c -S

memory.S : memory.c memory.h
	$(CC) memory.c -S

project_1.S : project_1.c project_1.h data.h memory.h
	$(CC) project_1.c -S

main.S : main.c data.h memory.h project_1.h
	$(CC) main.c -S


# Compiling (but not linking) the source code files

compile-all : $(options_c)
	$(CC) $(options_c) $(CFLAGS)


# Individually compiles the .c file and converts it to a .o file 
# was previously $<

%.o : %.c
	$(CC) $(CFLAGS) -c $^

# Build - compiling and linking

build : $(options_c)
	$(CC) data.c $(CFLAGS)
	$(CC) memory.c $(CFLAGS)
	$(CC) project_1.c $(CFLAGS)
	$(CC) main.c $(CFLAGS)
	$(CC) -o project $(options_o)


# Connection to beaglebone and uploading the executable

upload: 
	scp project root@192.168.7.2:/home/


# Creating an archive of my .c files and naming it libproject1.a

build-lib:
	ar -cvq libproject1.a *.c


# Phony targets
.PHONY : clean
clean:
	rm -rf *.o *.map *.i *.s project
