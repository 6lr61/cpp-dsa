VPATH = src:../headers
DIST = dist
CPPFLAGS = 
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++2b

all: $(DIST)/test dist

dist:
	mkdir dist

$(DIST)/test: linked-list/test.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

PHONY clean:
clean:
	-rm dist/*