/**
* ActorNode.cpp
* Author: Bhanu Vikas Renukuntla & Dion Chung
* Date:   16th Nov 2016
*
* A class, instances of which are Actor nodes stores the pointers to the movies
* of the actor
*/

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
    int years;
    bool isVisited;
    pair<MovieNode<ActorNode>*, ActorNode*> previous;

    ActorNode(string name);

    bool operator<(const ActorNode& other);

};



#endif // ACTORNODE_H
