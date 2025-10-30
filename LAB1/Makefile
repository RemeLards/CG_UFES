CXX = g++
CFLAGS = -g -Wall
LINKING = -lglut -lGL -lGLU

SOURCES = $(wildcard *.cpp)
TARGETS = $(SOURCES:.cpp=)

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CFLAGS) -o $@ $< $(LINKING)

clean:
	rm -f $(TARGETS)