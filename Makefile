CXX      = g++

CXXFLAGS  += -g -Wall -std=c++17 -pedantic -pthread -O3 -DNDEBUG

.DEFAULT_GOAL := all

SOURCES = $(wildcard src/*.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

%.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

CLEAN_OBJECTS = $(OBJECTS)
TARGETS = main

main: $(OBJECTS) $(OBJECTS)
	$(CXX) -pthread $(OBJECTS) -o $@ $(LDFLAGS)

all : main

########## cleanup ##########
DEPS = $(CLEAN_OBJECTS:.o=.d)

clean:
	@rm -f $(DEPS) $(TARGETS) $(CLEAN_OBJECTS)

-include $(DEPS)
