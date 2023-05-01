###
### Makefile for Gerp
###
###
### Authors: Toki Eashir(ttoki01) and Anh Hoang(ahoang05)
###

MAKEFLAGS += -L

CXX      = clang++ 
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -O2
LDFLAGS  = -g3

gerp: main.o stringProcessing.o gerp.o hashmap.o FSTree.o DirNode.o
	${CXX} ${CXXFLAGS} -o gerp $^

main.o: main.cpp gerp.h 
	$(CXX) $(CXXFLAGS) -c main.cpp

gerp.o: gerp.cpp gerp.h hashmap.h stringProcessing.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp

hashmap.o: hashmap.cpp hashmap.h 
	$(CXX) $(CXXFLAGS) -c hashmap.cpp

stringProcessing.o: stringProcessing.h stringProcessing.cpp
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

## Rules for compiling unit test
unit_test: unit_test_driver.o stringProcessing.o hashmap.o gerp.o DirNode.o \
		   FSTree.o
	$(CXX) $(CXXFLAGS) $^

provide:
	provide comp15 proj4_gerp main.cpp \
	gerp.cpp gerp.h hashmap.cpp hashmap.h \
	stringProcessing.h stringProcessing.cpp README Makefile unit_tests.h

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean:
	rm main.o gerp.o hashmap.o *~ a.out