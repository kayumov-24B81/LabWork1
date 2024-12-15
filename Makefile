PROJECT = bmp

LIBPROJECT = $(PROJECT).a

OBJECTS = main.o image.o matrix.o

DEPS = (wildcard *.hpp)

A = ar

AFLAGS = rsv

CXX = g++

CXXFLAGS = -I. -std=c++17 -Werror -Wpedantic -Wall -g -fPIC

LDXXFLAGS = $(CXXFLAGS) -L. -l:$(LIBPROJECT)

.PHONY: default

default: all;

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(PROJECT): main.o $(LIBPROJECT)
	$(CXX) -o $@ main.o $(LDXXFLAGS)
	
$(LIBPROJECT): $(OBJECTS)
	$(A) $(AFLAGS) $@ $^
	
all: $(PROJECT)

.PHONY: clean

clean:
	rm -f *.o

cleanall: clean
	rm -f $(LIBPROJECT)
	rm -f $(PROJECT)
	rm -f rotated_right.bmp rotated_left.bmp filtered.bmp




