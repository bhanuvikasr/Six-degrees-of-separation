/**
* ContactGraph.h
* Author: Bhanu Vikas Renukuntla & Dion Chung
* Date:   16th Nov 2016
*
* ContactGraph is a container for Person nodes for epidemic modeling
*/

#ifndef CONTACTGRAPH_H
#define CONTACTGRAPH_H

#include <iostream>
#include <unordered_map>
#include "Person.h"

using namespace std;

class ContactGraph {
public:
  int oldestYear = 9999;

  // unordered_map of IDs, Person node pointers
  unordered_map<int, Person*> people_map;

  ContactGraph(void);

  /* Destructor function
   *
   */
  ~ContactGraph();

  /** You can modify this method definition as you wish
   *
   * Load the graph from a tab-delimited file of actor->movie relationships.
   *
   * in_filename - input filename
   * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
   *
   * return true if file was loaded sucessfully, false otherwise
   */
  bool loadFromFile(const char* in_filename);
  void reset();
};


#endif // CONTACTGRAPH_H
