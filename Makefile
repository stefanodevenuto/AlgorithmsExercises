
CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: bin/test #bin/sorted_array_app

clean:
	$(RM) -rf bin/*
	$(RM) -rf build/*

build/sorting.o: src/sorting.c include/sorting.h
	$(CC) $(CFLAGS) -c src/sorting.c -o build/sorting.o

#bin/sorted_array_app: include/sorted_array.h build/sorted_array.o sorted_array_app/sorted_array_app.c
#	$(CC) $(CFLAGS) -o bin/sorted_array_app build/sorted_array.o sorted_array_app/sorted_array_app.c

bin/test: test/sorting_tests.c build/sorting.o include/sorting.h
	$(CC) $(CFLAGS)  test/sorting_tests.c build/sorting.o Resources/C/Unity/unity.c -o bin/test