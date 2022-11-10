CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./entry/main.cpp ./src/reader.cpp ./includes/reader.hpp
	$(CXX) $(CXXFLAGS) ./entry/main.cpp ./src/reader.cpp -o $@

# bin/tests: ./tests/tests.cc obj/catch.o ./src/circular-linked-list.cc ./includes/circular-linked-list.hpp ./includes/node.hpp
# 	$(CXX) $(CXXFLAGS) ./tests/tests.cc obj/catch.o ./src/circular-linked-list.cc -o $@

# obj/catch.o: tests/catch.cc
# 	$(CXX) $(CXXFLAGS) -c $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* 
