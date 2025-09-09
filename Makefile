PROJECT = bmp

COUNTER = count

LIBPROJECT = $(PROJECT).a

OBJECTS = main.o image.o matrix.o

DEPS = (wildcard *.hpp)

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

$(COUNTER): counting.o $(LIBPROJECT)
	$(CXX) -o $@ counting.o $(LDXXFLAGS)
	
$(LIBPROJECT): $(OBJECTS)
	$(A) $(AFLAGS) $@ $^
	
all: $(PROJECT)

counter: $(COUNTER)

.PHONY: clean

clean:
	rm -f *.o

cleanall: clean
	rm -f $(LIBPROJECT)
	rm -f $(PROJECT)
	rm -f $(COUNTER)
	rm -f rotated_right.bmp rotated_left.bmp filtered.bmp




