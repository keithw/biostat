AM_CXXFLAGS = $(PICKY_CXXFLAGS)

bin_PROGRAMS = cptester bsctester bbbtester bbbgrapher
cptester_SOURCES = cptester.cc clopper-pearson.hh clopper-pearson.cc \
	util.hh util.cc

bsctester_SOURCES = bsctester.cc clopper-pearson.hh clopper-pearson.cc \
	util.hh util.cc blyth-still-casella.hh blyth-still-casella.cc \
	binary-search.cc binary-search.hh

bbbtester_SOURCES = bbbtester.cc clopper-pearson.hh clopper-pearson.cc \
	util.hh util.cc blyth-still-casella.hh blyth-still-casella.cc \
	barbardbb.hh barnardbb.cc binary-search.cc binary-search.hh

bbbgrapher_SOURCES = bbbgrapher.cc clopper-pearson.hh clopper-pearson.cc \
	util.hh util.cc blyth-still-casella.hh blyth-still-casella.cc \
	barbardbb.hh barnardbb.cc binary-search.cc binary-search.hh
