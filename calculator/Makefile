# Makefile для калькулятора. Королев 25ПИ2.

.PHONY: all debug release clean

CXX = g++
RELEASE_FLAGS = -O2 -Wall -DNDEBUG
DEBUG_FLAGS   = -g -O0 -Wall
SOURCE        = calculator.cpp
RELEASE_EXEC  = calculator
DEBUG_EXEC    = calculator-dbg

all: debug release

debug: $(DEBUG_EXEC)

$(DEBUG_EXEC): $(SOURCE)
	$(CXX) $(DEBUG_FLAGS) $(SOURCE) -o $(DEBUG_EXEC)

release: $(RELEASE_EXEC)

$(RELEASE_EXEC): $(SOURCE)
	$(CXX) $(RELEASE_FLAGS) $(SOURCE) -o $(RELEASE_EXEC)

clean:
	rm -rf $(RELEASE_EXEC) $(DEBUG_EXEC) $(RELEASE_EXEC).dSYM $(DEBUG_EXEC).dSYM *.o
