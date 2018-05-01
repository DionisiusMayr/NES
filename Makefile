CC = g++
CFLAGS = -Wall -Wextra -std=c++14 -O2
OBJECTS = main.o
VPATH = src build

run: nes
	build/nes

main.o:
	$(CC) $(CFLAGS) -c src/main.cpp -o build/main.o

nes: $(OBJECTS)
	$(CC) $(CFLAGS) -o build/nes build/$(OBJECTS)

clean:
	rm -f build/nes build/$(OBJECTS)
