#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include "ActorGraph.h"

using namespace std;


void BFS(ActorNode* actor1, ActorNode* actor2) {
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
}

void outputPath(ActorNode* actor, ofstream & out) {
  string path = "(" + actor->name + ")";
  string temp;
  while (actor->previous.second) {
    temp = "(" + actor->previous.second->name + ")--[" + actor->previous.first->name + "#@" + to_string(2016 - actor->previous.first->weight) + "]-->";
    // cout << actor->previous.first->name << " and " << actor->previous.second->name << " at distance " << actor->years << endl;
    path = temp + path;
    actor = actor->previous.second;
  }
  out << path + "\n";
}

void reset(ActorGraph& G) {
  for (auto it = G.actors_map.begin(); it != G.actors_map.end(); ++it) {
    it->second->years = -1;
    it->second->previous = {NULL, NULL};
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

  ifstream in;
  in.open(find_pairs);
  ofstream out;
  out.open(output);

  // read argv[1] to create an actor graph
  ActorGraph G;
  G.loadFromFile(movie_casts, isUnweighted);

  out << "(actor)--[movie#@year]-->(actor)--...\n";
  // for each line in the find_pairs
  bool have_header = false;

  while (in) {
      string s;

      // get the next line
      if (!getline( in, s )) break;

      if (!have_header) {
          // skip the header
          have_header = true;
          continue;
      }
      istringstream ss( s );
      vector <string> record;

      while (ss) {
          string next;

          // get the next string before hitting a tab character and put it in 'next'
          if (!getline( ss, next, '\t' )) break;

          record.push_back( next );
      }

      if (record.size() != 2) {
          // we should have exactly 2 columns
          continue;
      }
      string actor1_name(record[0]);
      string actor2_name(record[1]);

      // we have actor1 and actor2, now what?
      ActorNode* actor1 = G.actors_map.at(actor1_name);
      ActorNode* actor2 = G.actors_map.at(actor2_name);
      // if(actor1 && actor2 != NULL){
        BFS(actor1, actor2);
        outputPath(actor2, out);
        reset(G);
      // }
      // else{
      //   std::cout << "Hello there you got a problem" << std::endl;
      // }

  }

  if (!in.eof()) {
      cerr << "Failed to read " << find_pairs << "!\n";
      return false;
  }


  in.close();
  out.close();


}
