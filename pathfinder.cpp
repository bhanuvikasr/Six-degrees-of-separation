#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ActorGraph.h"

using namespace std;

int main(int argc, char**argv){

  char* const movie_casts = argv[1];
  string edge_weight = argv[2];
  string find_pairs = argv[3];
  string output = argv[4];
  bool isUnweighted = 0;
  if (edge_weight == "u"){
    isUnweighted = 1;
  }

  // read argv[1] to create an actor graph
  ActorGraph G;

  G.loadFromFile(movie_casts,isUnweighted);

  string name = "50 CENT";

  ActorNode* actor = G.actors_map[name];
  if(actor==NULL){
    cout<< "Node doesn't exist for " << name<< endl;
  }
  else{

    for (auto it = actor->movies.begin(); it!=actor->movies.end(); it++){
      MovieNode<ActorNode>* mv = *it;
      cout << mv->name << endl;
    }
  }


}
