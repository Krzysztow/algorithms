#g++ ./main-1.1.cpp -o ./ch-1.1

CC=g++
CFLAGS=-c -Wall -ggdb
LDFLAGS=
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ch-1.2

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
	rm ./*.o
	rm $(EXECUTABLE)
	
debug:
	CFLAGS+=-ggdb
	make
