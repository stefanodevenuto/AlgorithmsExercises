
CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: bin/test bin/sorting_app

clean:
	$(RM) -rf bin/*
	$(RM) -rf build/*

build/sorting.o: src/sorting.c include/sorting.h
	$(CC) $(CFLAGS) -c src/sorting.c -o build/sorting.o

bin/sorting_app: include/sorting.h build/sorting.o sorting_app/sorting_app.c
	$(CC) $(CFLAGS) -o bin/sorting_app build/sorting.o sorting_app/sorting_app.c

bin/test: test/sorting_tests.c build/sorting.o include/sorting.h
	$(CC) $(CFLAGS)  test/sorting_tests.c build/sorting.o Resources/C/Unity/unity.c -o bin/test