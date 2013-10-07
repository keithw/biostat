source = util.cc binary-search.cc clopper-pearson.cc cptester.cc blyth-still-casella.cc bsctester.cc coverage-graph.cc barnardbb.cc bbbtester.cc bbbgrapher-slow.cc
objects = util.o binary-search.o clopper-pearson.o blyth-still-casella.o coverage-graph.o barnardbb.o
executables = cptester bsctester bbbtester bbbgrapher-slow

CXX = g++
LANGFLAGS = -std=c++0x
CXXFLAGS = -g -O3 $(LANGFLAGS) -pedantic -Werror -Wall -Wextra -Weffc++ -fno-default-inline -pipe
LIBS =

all: $(executables)

cptester: cptester.o $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LIBS)

bsctester: bsctester.o $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LIBS)

bbbtester: bbbtester.o $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LIBS)

bbbgrapher-slow: bbbgrapher-slow.o $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

-include depend

depend: $(source)
	$(CXX) $(INCLUDES) $(LANGFLAGS) -MM $(source) > depend

.PHONY: clean
clean:
	-rm -f $(executables) depend *.o *.rpo
