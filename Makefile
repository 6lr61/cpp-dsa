VPATH = src
DIST = dist
CPPFLAGS = 
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++23
CXX = g++

all: $(DIST)/test dist

dist:
	mkdir dist

$(DIST)/test: linked-list/test.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

PHONY clean:
clean:
	-rm dist/*
