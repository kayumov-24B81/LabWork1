PROJECT = bmp

COUNTER = count

LIBPROJECT = $(PROJECT).a

SRC_DIR = src

INCLUDE_DIR = include

OBJECTS = main.o image.o matrix.o

DEPS = $(wildcard $(INCLUDE_DIR)/*.hpp)

A = ar

AFLAGS = rsv

CXX = g++

CXXFLAGS = -I$(INCLUDE_DIR) -std=c++17 -Werror -Wpedantic -Wall -g -fPIC

LDXXFLAGS = $(CXXFLAGS) -L. -l:$(LIBPROJECT)

.PHONY: default

default: all;

obj/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	@mkdir -p obj
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	
$(LIBPROJECT): $(addprefix obj/, $(OBJECTS))
	$(A) $(AFLAGS) $@ $^
	

$(PROJECT): obj/main.o $(LIBPROJECT)
	$(CXX) -o $@ $< $(LDXXFLAGS)

$(COUNTER): obj/counter.o $(LIBPROJECT)
	$(CXX) -o $@ $< $(LDXXFLAGS)

all: $(PROJECT)

counter: $(COUNTER)

.PHONY: clean

clean:
	rm -f obj/*.o

cleanall: clean
	rm -f $(LIBPROJECT)
	rm -f $(PROJECT)
	rm -f $(COUNTER)
	rm -f rotated_right.bmp rotated_left.bmp filtered.bmp




