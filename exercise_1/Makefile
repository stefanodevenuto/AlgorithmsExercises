
CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: bin/test bin/sorting_app

clean:
	$(RM) -rf bin/*
	$(RM) -rf build/*

build/sorting.o: src/sorting.c include/sorting.h
	$(CC) $(CFLAGS) -c src/sorting.c -o build/sorting.o

build/dyn_array.o: src/dyn_array.c include/dyn_array.h
	$(CC) $(CFLAGS) -c src/dyn_array.c -o build/dyn_array.o

bin/sorting_app: include/sorting.h build/sorting.o include/dyn_array.h build/dyn_array.o sorting_app/sorting_app.c
	$(CC) $(CFLAGS) -o bin/sorting_app build/sorting.o build/dyn_array.o sorting_app/sorting_app.c

bin/test: test/sorting_tests.c build/sorting.o include/sorting.h
	$(CC) $(CFLAGS)  test/sorting_tests.c build/sorting.o Resources/C/Unity/unity.c -o bin/test