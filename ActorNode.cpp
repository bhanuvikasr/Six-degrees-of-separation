/**
* ActorNode.cpp
* Author: Bhanu Vikas Renukuntla & Dion Chung
* Date:   16th Nov 2016
*
* A class, instances of which are Actor nodes stores the pointers to the movies
* of the actor
*/
#include "ActorNode.h"
#include "MovieNode.h"
#include <vector>


// method for creating and initialising a node;
ActorNode::ActorNode(string name) : name(name), years(-1), previous({NULL, NULL}) {}
