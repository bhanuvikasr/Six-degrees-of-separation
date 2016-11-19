/*
 * pathfinder.cpp
 * Author: Bhanu Vikas Renukuntla & Dion Chung
 * Date:   16th Nov 2016
 *
 * This file has methods to find shortest path between any 2 given ActorNodes.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include "ActorGraph.h"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<ActorNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on ActorNodes.
 */
class ActorNodePtrComp {
public:
    bool operator()(ActorNode*& lhs, ActorNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/** A function to iterate over the graph using BFS algorithm to find the
    shortest path between actor1 and actor2
 */
bool BFS(ActorNode* actor1, ActorNode* actor2) {
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
      return true;
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
  return false;
}

/** A function to iterate over the graph using Dijkstra's algorithm to find the
    shortest path between actor1 and actor2 over weighted edges.
 */
bool dijkstra(ActorNode* actor1, ActorNode* actor2) {
  priority_queue<ActorNode*, vector<ActorNode*>, ActorNodePtrComp> actor_queue;

  actor_queue.push(actor1);
  while (!actor_queue.empty()) {
    ActorNode* n = actor_queue.top();
    actor_queue.pop();
    if (n->isVisited) {
      continue;
    }

    if (!n->previous.second) {
      n->years = 0;
    }

    n->isVisited = true;

    for (int i=0; i<n->movies.size(); i++) {
      for (int j=0; j<n->movies[i]->cast.size(); j++) {
        ActorNode* next = n->movies[i]->cast[j];
        int nextWeight = n->years + n->movies[i]->weight;
        if (next->name!=n->name && next->isVisited==false && (nextWeight < next->years || next->years == -1)) {
          next->years = nextWeight;
          next->previous = make_pair(n->movies[i], n);
          actor_queue.push(next);
        }
      }
    }
  }
  return true;
}


/** A function to backtrace the shortest path found by BFS function using
    previous variable in the ActorNode.
 */
void outputPath(ActorNode* actor, ofstream & out) {
  string path = "(" + actor->name + ")";
  string temp;
  while (actor->previous.second) {
    temp = "(" + actor->previous.second->name + ")--[" + actor->previous.first->name + "#@" + to_string(2016 - actor->previous.first->weight) + "]-->";
    path = temp + path;
    actor = actor->previous.second;
  }
  out << path + "\n";
}

/** A function to reset the years and previous variables in ActorNode to -1 and
    {NULL,NULL} respectively. Needed for BFS function to work properly.
 */
void reset(ActorGraph& G) {
  for (auto it = G.actors_map.begin(); it != G.actors_map.end(); ++it) {
    if (it->second != NULL) {
      it->second->years = -1;
      it->second->previous = {NULL, NULL};
      it->second->isVisited = false;
    }
  }
}

/** MAIN function
 */
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

  bool have_header = false;
  // for each line in the find_pairs

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

      auto it1 = G.actors_map.find(actor1_name);
      auto it2 = G.actors_map.find(actor2_name);
      if(it1 != G.actors_map.end() && it2 != G.actors_map.end()) {
        ActorNode* actor1 = G.actors_map.at(actor1_name);
        ActorNode* actor2 = G.actors_map.at(actor2_name);

        bool foundPath;
        if (isUnweighted) foundPath = BFS(actor1, actor2);
        else foundPath = dijkstra(actor1, actor2);

        if (foundPath) {
          outputPath(actor2, out);
        }
        else {
          // TODO correct handling of disconnected actors
        }
        reset(G);
      }
      else{
        // TODO correct handling bad actor names
        std::cout << "One or more of the actors is invalid" << std::endl;
      }
  }

  if (!in.eof()) {
      cerr << "Failed to read " << find_pairs << "!\n";
  }


  in.close();
  out.close();

  return 0;
}
