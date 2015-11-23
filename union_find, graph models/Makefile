CPP      = g++
CPPFLAGS = -c -g -Wall -pedantic -std=c++11

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<

SRC = graph.cpp union_find.cpp 
H   = edge.hpp graph.hpp union_find.hpp

SRC = graph.cpp

all: dependencies grr uf

dependencies: $(SRC) $(H)
	 rm -f dependencies
	 $(CC) $(CPPFLAGS) -MM $(SRC) >> dependencies

include dependencies

all: grr uf

grr: grr.o graph.o
	g++ -o grr -g grr.o graph.o

uf: uf.o union_find.o
	g++ -o uf -g uf.o union_find.o
clean: 
	rm dependencies uf.o graph.o grr.o union_find.o
