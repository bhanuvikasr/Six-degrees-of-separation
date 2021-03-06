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
#include "traversalfunctions.cpp"

using namespace std;

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
