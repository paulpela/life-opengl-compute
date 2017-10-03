CC=clang++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=-lGLEW -lglfw3 -lGL
SOURCES=main.cpp buddha.cpp cube.cpp keyboard.cpp shader.cpp utils.cpp window.cpp texgens.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=a.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	    $(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	    $(CC) $(CFLAGS) $< -o $@

run: all
	./$(EXECUTABLE)

clean:
	-rm -f a.out
	-rm -f *.o
