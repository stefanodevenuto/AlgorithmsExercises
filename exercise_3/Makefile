
CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: bin/test bin/hashmap_app

build/hashmap.o: src/hashmap.c include/hashmap.h
	$(CC) $(CFLAGS) -c src/hashmap.c -o build/hashmap.o

bin/hashmap_app: include/hashmap.h build/hashmap.o hashmap_app/hashmap_app.c
	$(CC) $(CFLAGS) -o bin/hashmap_app build/hashmap.o hashmap_app/hashmap_app.c

bin/test: test/hashmap_tests.c build/hashmap.o include/hashmap.h
	$(CC) $(CFLAGS) test/hashmap_tests.c build/hashmap.o Resources/C/Unity/unity.c -o bin/test