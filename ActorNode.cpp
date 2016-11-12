#include "ActorNode.h"
#include "MovieNode.h"
#include <vector>


// method for creaitng and initialising a node;


// method for adding a new movie;
bool ActorNode::Add_movie(MovieNode* new_movie){
  if(new_movie != NULL){
    movies.push_back(new_movie);
    return true;
  }
  return false;
}
