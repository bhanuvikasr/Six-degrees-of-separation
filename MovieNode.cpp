#include "ActorNode.h"
#include "MovieNode.h"
#include <vector>



// method for adding a new cast;
bool MovieNode::Add_cast(ActorNode* new_cast){
// bool MovieNode::Add_cast(int new_cast){
  if(new_cast !=NULL){
    cast.push_back(new_cast);
    return true;
  }
  return false;
}
