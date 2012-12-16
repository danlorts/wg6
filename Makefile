#         _   
#       _|_   
#   \/\(_|_)
#       _|    
# 
# This Makefile builds wg6, the genetic multicore schedule solver. Invoke `make
# help' for a list of targets.

# Set some compile-time info
DATE := $(shell date)
REV := $(shell if [ -e /usr/bin/git ]; then git rev-parse --short HEAD; else echo unknown; fi)
DEFINES = -DBUILDDATE="\"$(DATE)\"" -DBUILDREV="\"$(REV)\""

# Pick a compiler. The combination of C++11 and OpenMP only really works on
# g++ for now.
CXX := g++

# We want C++11 and OpenMP.
FLAGS ?= -std=c++11 -fopenmp

# We want as many warnings as possible, optimization, and fast math.
WARNFLAGS ?= -Wall -Wextra -Werror -pedantic
DEBUGFLAGS ?= -g
OPTFLAGS ?= -Os -ffast-math
CXXFLAGS ?= $(WARNFLAGS) $(DEBUGFLAGS) $(OPTFLAGS) $(FLAGS) $(DEFINES)

# We link against libsigsegv and gperftools.
LDFLAGS ?= -lsigsegv -lprofiler -ltcmalloc

# List every .o file here.
OBJECTS = wg6.o config.o\
		  Event.o\
		  FitnessFunction.o\
		  Parser.o\
		  Population.o\
		  Problem.o\
		  Solution.o\

# Build wg6, dependency information, and a ctags file by default
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

prof: wg6
	@env CPUPROFILE=/tmp/wg.prof ./wg6
	@pprof --text ./wg6 /tmp/wg.prof

help:
	@echo "The following make targets are available:"
	@cat Makefile|grep -o -E "^([a-z0-9]*): "|sort|sed 's/://g'|sed 's/^/    - /g'

include deps

.PHONY: prof clean help
