
CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: bin/test

build/hashmap.o: src/hashmap.c include/hashmap.h
	$(CC) $(CFLAGS) -c src/hashmap.c -o build/hashmap.o

bin/test: test/hasmap_tests.c build/hashmap.o include/hashmap.h
	$(CC) $(CFLAGS)  test/hasmap_tests.c build/hashmap.o Resources/C/Unity/unity.c -o bin/test