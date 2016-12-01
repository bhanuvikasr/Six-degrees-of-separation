# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder actorconnections extension



# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o MovieNode.o ActorNode.o
actorconnections: ActorGraph.o MovieNode.o ActorNode.o UFActorNode.o
extension: Person.o ContactGraph.o


# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

ActorGraph.o: UnionFind.hpp MovieNode.h ActorNode.h ActorGraph.h traversalfunctions.cpp
MovieNode.o: MovieNode.h
ActorNode.o: ActorNode.h
UFActorNode.o: UFActorNode.h
Person.o: Person.h
ContactGraph.o: ContactGraph.h Person.h


clean:
	rm -f pathfinder actorconnections extension *.o core*
