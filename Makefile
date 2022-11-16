# appname := game

# CXX := g++
CXXFLAGS := -std=c++11 -pthread $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)

game.exe: main.cxx src/func.cpp include/func.hpp
	g++ -o game.exe src/func.cpp main.cxx $(CXXFLAGS) $(LDFLAGS)

# srcfiles := $(shell find . -name "*.hpp")
# objects  := $(patsubst %.h, %.o, $(srcfiles))

# all: $(appname)

# $(appname): $(objects)
# 	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

# depend: .depend

# .depend: $(srcfiles)
# 	rm -f ./.depend
# 	$(CXX) $(CXXFLAGS) $(LDFLAGS) -MM $^>>./.depend;

# clean:
# 	rm -f $(objects)

# dist-clean: clean
# 	rm -f *~ .depend

# include .depend
