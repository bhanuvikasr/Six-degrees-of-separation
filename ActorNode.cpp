#include "ActorNode.h"
#include "MovieNode.h"
#include <vector>


// method for creatng and initialising a node;
ActorNode::ActorNode(string name) : name(name), years(-1), previous({NULL, NULL}) {}

// method for adding a new movie;
bool ActorNode::addMovie(MovieNode<ActorNode>* new_movie){
  if(new_movie != NULL){
    movies.push_back(new_movie);
    return true;
  }
  return false;
}
