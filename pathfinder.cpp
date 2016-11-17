#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include "ActorGraph.h"
#include "BFSNode.h"

using namespace std;

// bool BFS(ActorNode* actor1, ActorNode* actor2, vector<pair<string, string>>& path) {
//   queue<BFSNode*> bfs_queue;
//
//   BFSNode* root = new BFSNode(actor1);
//   root->movie = actor1->movies[0];
//   root->p = NULL;
//   bfs_queue.push(root);
// }

void BFS(ActorNode* actor1, ActorNode* actor2) {
  // queue<pair<MovieNode<ActorNode>*, ActorNode*>> bfs_queue;
  queue<ActorNode*> bfs_queue;

  bfs_queue.push(actor1);
  while (!bfs_queue.empty()) {
    ActorNode* n = bfs_queue.front();
    bfs_queue.pop();
    if (n->years != -1) {
      continue;
    }

    if (!n->previous.second) {
      n->years = 0;
    }
    else {
      n->years = n->previous.second->years + 1;
    }

    if (n->name==actor2->name) {
      break;
    }

    for (int i=0; i<n->movies.size(); i++) {
      for (int j=0; j<n->movies[i]->cast.size(); j++) {
        ActorNode* next = n->movies[i]->cast[j];
        if (next->name!=n->name && next->years==-1 && next->previous.second==NULL) {
          next->previous = make_pair(n->movies[i], n);
          bfs_queue.push(next);
        }
      }
    }
  }

  ActorNode* n2 = actor2;
  while (n2->previous.second) {
    cout << n2->previous.first->name << " and " << n2->previous.second->name << " at distance " << n2->years << endl;
    n2 = n2->previous.second;
  }
}

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
  G.loadFromFile(movie_casts, isUnweighted);

  string name1 = "50 CENT";
  ActorNode* actor1 = G.actors_map[name1];
  string name2 = "ABKARIAN, SIMON";
  ActorNode* actor2 = G.actors_map[name2];

  BFS(actor1, actor2);


}
