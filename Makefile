source = util.cc binary-search.cc clopper-pearson.cc cptester.cc blyth-still-casella.cc bsctester.cc coverage-graph.cc barnardbb.cc bbbtester.cc
objects = util.o binary-search.o clopper-pearson.o blyth-still-casella.o coverage-graph.o barnardbb.o
executables = cptester bsctester bbbtester

CXX = g++
CXXFLAGS = -g -O3 -std=c++0x -ffast-math -pedantic -Werror -Wall -Wextra -Weffc++ -fno-default-inline -pipe -D_FILE_OFFSET_BITS=64 -D_XOPEN_SOURCE=500 -D_GNU_SOURCE
LIBS = -lm

all: $(executables)

cptester: cptester.o $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LIBS)

bsctester: bsctester.o $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LIBS)

bbbtester: bbbtester.o $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

-include depend

depend: $(source)
	$(CXX) $(INCLUDES) -MM $(source) > depend

.PHONY: clean
clean:
	-rm -f $(executables) depend *.o *.rpo
