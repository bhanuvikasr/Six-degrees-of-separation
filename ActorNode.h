#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <iostream>
#include <string>
#include <vector>
#include "MovieNode.h"

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes are the edges in the graph.
 */
class ActorNode{

public:
    string name;
    vector<MovieNode<ActorNode>*> movies;

    ActorNode(string name,
    vector<MovieNode<ActorNode>*> movies):name(name){}

    bool addMovie(MovieNode<ActorNode>* new_movie);

};



#endif // ACTORNODE_H
