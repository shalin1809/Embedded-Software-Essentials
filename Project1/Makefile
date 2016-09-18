
include sources.mk


# Compiler variables
CC = gcc
BBB = arm-linux-gnueabihf-gcc
FRDM = arm-linux-none


# Setting the compiler flags
CFLAGS = -c -Wall -g -std=c99 -O0


# Setting phony targets 
.PHONY : preprocess data.i memory.i project_1.i main.i asm-file data.S memory.S project_1.S main.S \
    compile-all compile-all-BBB compile-all-FRDM %.o build build_BBB build_FRDM upload build-lib


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

asm-file : data.c memory.c main.c project_1.c
	$(CC) data.c memory.c main.c project_1.c -S 

data.S : data.c data.h
	$(CC) data.c -S

memory.S : memory.c memory.h
	$(CC) memory.c -S

project_1.S : project_1.c project_1.h data.h memory.h
	$(CC) project_1.c -S

main.S : main.c data.h memory.h project_1.h
	$(CC) main.c -S


# Compiling (but not linking) the source code files

compile-all : $(options_c) $(options_h)
	$(CC) $(options_c) $(CFLAGS)
	

compile-all-BBB : $(options_c) $(options_h)
	$(BBB) $(options_c) $(CFLAGS)
	

compile-all-FRDM : $(options_c) $(options_h)
	$(FRDM) $(options_c) $(CFLAGS)


# Individually compiles the .c file and converts it to a .o file 

%.o : %.c
	$(CC) $(CFLAGS) -c $^


# Build - compiling and linking

build : $(options_c) $(options_h)
	$(CC) data.c $(CFLAGS)
	$(CC) memory.c $(CFLAGS)
	$(CC) project_1.c $(CFLAGS)
	$(CC) main.c $(CFLAGS)
	$(CC) -o project $(options_o)
	
	
build_BBB : $(options_c) $(options_h)
	$(BBB) data.c $(CFLAGS)
	$(BBB) memory.c $(CFLAGS)
	$(BBB) project_1.c $(CFLAGS)
	$(BBB) main.c $(CFLAGS)
	$(BBB) -o project $(options_o)
	
	
build_FRDM : $(options_c) $(options_h)
	$(FRDM) data.c $(CFLAGS)
	$(FRDM) memory.c $(CFLAGS)
	$(FRDM) project_1.c $(CFLAGS)
	$(FRDM) main.c $(CFLAGS)
	$(FRDM) -o project $(options_o)


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
