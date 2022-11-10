CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./entry/main.cpp ./src/graph.cpp ./includes/graph.hpp
	$(CXX) $(CXXFLAGS) ./entry/main.cpp ./src/graph.cpp -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* 
