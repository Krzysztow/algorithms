#g++ ./main-1.1.cpp -o ./ch-1.1

CC=g++
CFLAGS=-c -g -Wall
LDFLAGS=-g
SOURCES=main.cpp
INCLUDEPATHS=
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(INCLUDEPATHS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $(INCLUDEPATHS) $< -o $@

clean:
	rm ./*.o
	rm $(EXECUTABLE)
