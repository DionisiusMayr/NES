CC = g++
CFLAGS = -Wall -Wextra -std=c++14 -O2
OBJ_FILES = Memory.o Opcodes.o Processor.o Registers.o main.o utility.o
OBJECTS = $(foreach file,$(OBJ_FILES),build/$(file))
# VPATH = src build
vpath %.c src
vpath %.o build

run: nes
	build/nes

nes: main.o
	$(CC) $(CFLAGS) -o build/nes build/main.o

Memory.o: utility.o
	$(CC) $(CFLAGS) -c src/Memory.cpp -o build/Memory.o

Opcodes.o:
	$(CC) $(CFLAGS) -c src/Opcodes.cpp -o build/Opcodes.o

Processor.o: Memory.o Registers.o Opcodes.o
	$(CC) $(CFLAGS) -c src/Processor.cpp -o build/Processor.o

Registers.o: utility.o
	$(CC) $(CFLAGS) -c src/Registers.cpp -o build/Registers.o

main.o: Registers.o Memory.o Processor.o
	$(CC) $(CFLAGS) -c src/main.cpp -o build/main.o

utility.o:
	$(CC) $(CFLAGS) -c src/utility.cpp -o build/utility.o

clean:
	rm -f build/nes $(OBJECTS)

