CC=clang
CFLAGS=-Wall -c -std=c++11 -stdlib=libc++ -lstring
LDFLAGS=
SOURCES=test.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

build: $(SOURCES) $(EXECUTABLE)

rebuild:
	make clean
	make build

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CXX) $(CFLAGS) $< -o $@

clean: 
	rm *.o $(EXECUTABLE)
