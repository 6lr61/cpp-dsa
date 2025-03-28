CATCH2_LIBS := $(shell pkg-config --libs catch2-with-main)
CATCH2_INCLUDES := $(shell pkg-config --cflags catch2-with-main)
CXXFLAGS = -g -Wall -Wextra -Wsign-conversion -Werror -Wpedantic -fsanitize=leak --std=c++23 $(CATCH2_INCLUDES)
CXX = g++

test: hash_map
	./$<

%: %.cpp ../src/%.hpp
	$(CXX) $(CPPLFAGS) $(CXXFLAGS) -o $@ $< $(CATCH2_LIBS)

PHONY: clean
clean:
	-rm linked_list binary_tree hash_map
