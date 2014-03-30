#g++ ./main-1.1.cpp -o ./ch-1.1

CC=gcc
CFLAGS=-c -g -Wall
LDFLAGS=-g
SOURCES=main.c ../include/arraystack.c
INCLUDEPATHS=-I../include/ 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(INCLUDEPATHS) $(OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) $(INCLUDEPATHS) $< -o $@

clean:
	rm ./*.o
	rm $(EXECUTABLE)
