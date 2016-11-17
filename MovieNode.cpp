#include "MovieNode.h"
#include <vector>


template<typename Data>
// method for adding a new cast;
bool MovieNode<Data>::addCast(Data* new_cast){
  if(new_cast !=NULL){
    cast.push_back(new_cast);
    return true;
  }
  return false;
}
