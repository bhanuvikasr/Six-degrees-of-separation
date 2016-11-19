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


// method for creating and initialising a node
ActorNode::ActorNode(string name) : name(name), years(-1), isVisited(false), previous({NULL, NULL}) {}

// overload < for priority_queue
bool ActorNode::operator<(const ActorNode& other) {
  if (this->years>other.years) {
    return true;
  }
  else if (this->years<other.years) {
    return false;
  }
  // prioritize alphabetically
  return (this->name<other.name);
}
