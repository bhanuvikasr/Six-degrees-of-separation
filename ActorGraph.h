/**
* ActorNode.cpp
* Author: Bhanu Vikas Renukuntla & Dion Chung
* Date:   16th Nov 2016
*
* This file is meant to exist as a container for starter code that you can use to read the input file format
* defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
*/

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <unordered_map>
#include "ActorNode.h"
#include "MovieNode.h"

// Maybe include some data structures here

using namespace std;

class ActorGraph {
protected:

    // Maybe add class data structure(s) here

public:
  int oldestYear = 9999;

  // unordered_map of movie names, movie node pointers
  unordered_map<string,MovieNode<ActorNode>*> movies_map;

  // unordered_map of actor_names, actor node pointers
  unordered_map<string,ActorNode*> actors_map;

  ActorGraph(void);

  /* Destructor function
   *
   */
  ~ActorGraph();




  /** You can modify this method definition as you wish
   *
   * Load the graph from a tab-delimited file of actor->movie relationships.
   *
   * in_filename - input filename
   * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
   *
   * return true if file was loaded sucessfully, false otherwise
   */
  bool loadFromFile(const char* in_filename, bool use_weighted_edges);



};


#endif // ACTORGRAPH_H
