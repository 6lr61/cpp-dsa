VPATH = src
DIST = dist

all: tests

tests:
	cd test && $(MAKE) 

clean:
	cd test && $(MAKE) clean
