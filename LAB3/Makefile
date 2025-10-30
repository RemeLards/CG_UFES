CXX = g++
CFLAGS = -g -Wall
LINKING = -lglut -lGL -lGLU

SOURCES = $(wildcard *.cpp)
TARGET = main

all: $(TARGET)

# Compila todos os .cpp em um único executável
$(TARGET): $(SOURCES)
	$(CXX) $(CFLAGS) -o $@ $^ $(LINKING)

clean:
	rm -f $(TARGET)
