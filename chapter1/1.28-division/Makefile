CC=g++
CFLAGS=-Wall
LDFLAGS=
SOURCES=main.cpp division.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=intDivide

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm $(EXECUTABLE)
	rm ./*.o
