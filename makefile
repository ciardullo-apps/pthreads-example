# makefile for deal

# Compiler
CC = gcc

# Linkage
LDFLAGS=-pthread

# C files
SOURCE_FILE = simplethread.c

# Executable file
OUT_FILE = simplethread

# Here is the build target, which compiles the two c files and
# generates the deal executable file
compile: $(SOURCE_FILE)
	$(CC) -o $(OUT_FILE) $(SOURCE_FILE) -I. $(LDFLAGS)

# Remove object files
clean:
	rm -f *.o core

build: clean compile
