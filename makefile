CC = gcc
AR=ar
FLAGS = -Wall -fPIC -g

all: graph graphs

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

graphs: graph.a

graph.a: graph.o main.o
	$(AR) -rcs  graph.a graph.o main.o

graph: main.o graph.o
	$(CC) $(FLAGS) -o graph main.o graph.o

clean:
	rm -f graph.a graph graphs *.o

.PHONY: clean all graph graphs