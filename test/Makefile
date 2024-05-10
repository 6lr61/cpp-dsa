CATCH2_LIBS := $(shell pkg-config --libs catch2-with-main)
CATCH2_INCLUDES := $(shell pkg-config --cflags catch2-with-main)
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic --std=c++2b $(CATCH2_INCLUDES)
CXX = g++

test: binary_tree
	./$<

binary_tree: binary_tree.cpp ../src/binary_tree.hpp
	$(CXX) $(CPPLFAGS) $(CXXFLAGS) -o $@ $< $(CATCH2_LIBS)

linked_list: linked_list.cpp ../src/linked_list.hpp
	$(CXX) $(CPPLFAGS) $(CXXFLAGS) -o $@ $< $(CATCH2_LIBS)


PHONY: clean
clean:
	-rm linked_list
