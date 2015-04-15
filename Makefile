CC=clang
CXX=clang++
CFLAGS=-Wall -c
CXXFLAGS=-g -std=c++11 -stdlib=libc++
LDFLAGS=
SOURCES=test.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

build: $(SOURCES) $(EXECUTABLE)

rebuild:
	make clean
	make build

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean: 
	rm *.o $(EXECUTABLE)
