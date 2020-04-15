
CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: build/hashmap.o bin/test Makefile

build/hashmap.o: src/hashmap.c include/hashmap.h
	$(CC) $(CFLAGS) -c src/hashmap.c -o build/hashmap.o

bin/test: test/hashmap_tests.c build/hashmap.o include/hashmap.h
	$(CC) $(CFLAGS) test/hashmap_tests.c build/hashmap.o Resources/C/Unity/unity.c -o bin/test