
CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: bin/graph_app

clean:
	$(RM) -rf bin/*
	$(RM) -rf build/*

build/graph.o: include/graph.h src/graph.c
	$(CC) $(CFLAGS) -c src/graph.c -o build/graph.o

bin/graph_app: include/graph.h build/graph.o graph_app/graph_app.c
	$(CC) $(CFLAGS) -o bin/graph_app build/graph.o graph_app/graph_app.c
