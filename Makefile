CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -Wpedantic -Iinclude
BIN      := build/rekursif
TEST     := build/test_rekursif

.PHONY: all test run clean
all: $(BIN)

build:
	mkdir -p build

$(BIN): src/main.cpp $(wildcard include/rekursif/*.hpp) | build
	$(CXX) $(CXXFLAGS) $< -o $@

$(TEST): tests/test_rekursif.cpp $(wildcard include/rekursif/*.hpp) | build
	$(CXX) $(CXXFLAGS) $< -o $@

test: $(TEST)
	./$(TEST)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf build
