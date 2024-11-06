PROJECT = bmp

LIBPROJECT = $(PROJECT).a

OBJECTS = main.o read.o write.o rotate_right.o rotate_left.o

DEPS = (wildcard *.h)

A = ar

AFLAGS = rsv

CXX = g++

CCXFLAGS = -I. -std=c++17 -Werror -Wpedantic -Wall -g -fPIC

LDXXFLAGS = $(CCXFLAGS) -L. -l:$(LIBPROJECT)

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
	rm -f rotated_right.bmp rotated_left.bmp




