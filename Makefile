CXX ?= g++
FLAGS ?= -std=c++11 -fopenmp
CXXFLAGS ?= -Wall -Wextra -Werror -pedantic -g -Os -pipe $(FLAGS)
LDFLAGS ?= -lboost_thread -lboost_system -lsigsegv

OBJECTS = wg6.o config.o\
		  FitnessFunction.o\
		  Event.o\
		  Parser.o\
		  Problem.o\
		  Population.o\
		  Solution.o\
		  SolverThread.o

# Targets
all: wg6 deps tags

wg6: $(OBJECTS)
	@echo "- Linking wg6..."
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	@echo "- Compiling ($(CXX)) $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

deps: $(wildcard *.cpp) $(wildcard *.h)
	@echo "- Recalculating dependencies..."
	@$(CXX) $(FLAGS) -MM *.cpp > deps

tags: $(wildcard *.cpp) $(wildcard *.h)
	@echo "- Collecting tags..."
	@ctags *.cpp

clean:
	@rm -rvf *.o

grind:
	@valgrind ./wg6 2>&1| vim -R -

include deps
