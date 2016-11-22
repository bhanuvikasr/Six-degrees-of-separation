/**
* ActorNode.cpp
* Author: Bhanu Vikas Renukuntla & Dion Chung
* Date:   16th Nov 2016
*
* A class, instances of which are Actor nodes stores the pointers to the movies
* of the actor
*/
#include "UFActorNode.h"
#include "MovieNode.h"
#include <vector>


// method for creating and initialising a node
UFActorNode::UFActorNode(string name) : name(name), yearConnected(0), size(1), previous(NULL) {}
