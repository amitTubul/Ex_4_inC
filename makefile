CC = gcc
AR=ar
FLAGS = -Wall -fPIC -g

all: main graphs
graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

graphs: graph.a

graph.a: graph.o main.o
	$(AR) -rcs  graph.a graph.o main.o

main: main.o graph.a
	$(CC) $(FLAGS) -o main main.o graph.a

clean:
	rm -f graph.a main graphs *.o

.PHONY: clean all main graphs