/**
* UFActorNode.cpp
* Author: Bhanu Vikas Renukuntla & Dion Chung
* Date:   16th Nov 2016
*
* A class, instances of which are Actor nodes stores the pointers to other actor
* nodes for UnionFind
*/

#ifndef UFACTORNODE_H
#define UFACTORNODE_H

#include <iostream>
#include <string>
#include <vector>

#include "MovieNode.h"

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes are the edges in the graph.
 */
class UFActorNode{

public:
    string name;
    int yearConnected;
    int size;
    UFActorNode* previous;

    UFActorNode(string name);

    // bool operator<(const ActorNode& other);

};



#endif // UFACTORNODE_H
