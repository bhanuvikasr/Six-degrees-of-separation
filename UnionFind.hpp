/*
 * UnionFind.hpp
 * Author: Bhanu Vikas Renukuntla & Dion Chung
 * Date:   16th Nov 2016
 *
 * This file has class declarations and definitions for UnionFind
 * data stucture.
 */

#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "UFActorNode.h"
#include "MovieNode.h"

#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

using namespace std;

class UnionFind {
public:

  map<string, MovieNode<UFActorNode>*> movies_map;
  unordered_map<string, UFActorNode*> actors_map;

  UnionFind(void);
  ~UnionFind();
  int getHeight(UFActorNode* n);
  bool join(vector<UFActorNode*> & ActorsList, int movie_year);
  UFActorNode* find(UFActorNode* n);
  int getYear(string actor1, string actor2);
  void loadFromFile(const char* in_filename);
  void buildGraph();
 };

UnionFind::UnionFind(void) {}

UnionFind::~UnionFind() {

}

int UnionFind::getHeight(UFActorNode *n) {
  int height = 0;
  while (n) {
    height++;
    n = n->previous;
  }
  return height;
}

bool UnionFind::join(vector<UFActorNode*> & ActorsList, int movie_year) {
  vector<UFActorNode*> headNodes;

  int max_size = 0;
  UFActorNode* head_max = find(ActorsList[0]);
  for (int i = 0; i < ActorsList.size(); i++) {
    UFActorNode* temp_head_max = find(ActorsList[i]);
    headNodes.push_back(temp_head_max);
    int size = ActorsList[i]->size;
    if(max_size < size){
      max_size = size;
      head_max = temp_head_max;
    }
  }

  for(int j = 0; j < headNodes.size(); j++) {
    UFActorNode* temp = headNodes[j];
    if(temp->name != head_max->name){ // only connects sets which are disconnected
      temp->previous = head_max;
      temp->yearConnected = movie_year;
      head_max->size += temp->size;
    }
  }

  return false;
}

UFActorNode* UnionFind::find(UFActorNode* n) {
  while (n->previous) {
    n = n->previous;
  }
  return n;
}

int UnionFind::getYear(string actor1, string actor2) {
  UFActorNode* a1 = actors_map[actor1];
  UFActorNode* a2 = actors_map[actor2];
  UFActorNode* head1 = find(a1);
  UFActorNode* head2 = find(a2);
  int maxYear = 0;
  if(head1->name == head2->name){
    int h1 = getHeight(a1);
    int h2 = getHeight(a2);
    if (h1 > h2) {
      swap(h1, h2);
      swap(a1, a2);
    }
    int dh = h2 - h1;
      for (int h = 0; h < dh; h++) {
        if (maxYear < a2->yearConnected) maxYear = a2->yearConnected;
        a2 = a2->previous;
      }
      while (a1 && a2) {
        if (a1->name == a2->name) return maxYear;
        if (maxYear < a1->yearConnected) maxYear = a1->yearConnected;
        a1 = a1->previous;
        if (maxYear < a2->yearConnected) maxYear = a2->yearConnected;
        a2 = a2->previous;
      }
      return 0;
  }
  else{
    return 0;
  }
}

void UnionFind::loadFromFile(const char* in_filename) {
  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (infile) {
      string s;

      // get the next line
      if (!getline( infile, s )) break;

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

      if (record.size() != 3) {
          // we should have exactly 3 columns
          continue;
      }

      string actor_name(record[0]);
      string movie_title(record[1]);
      int movie_year = stoi(record[2]);

      UFActorNode* actor = actors_map[actor_name];
      if(actor == nullptr){
        // create an actor node
        actor = new UFActorNode(actor_name);
        actors_map[actor_name] = actor;
      }
      int weight = 2016 - movie_year;
      string movie_key = to_string(movie_year) + movie_title;
      MovieNode<UFActorNode>* movie = movies_map[movie_key];
      if(movie == NULL){
        // create a movie node
        movie = new MovieNode<UFActorNode>(movie_title, weight);
        movies_map[movie_key] = movie;
      }
      movie->cast.push_back(actor);
  }
}

void UnionFind::buildGraph() {
  for(auto it = movies_map.begin(); it != movies_map.end(); it++) {
    int movie_year = 2016 - it->second->weight;
    join(it->second->cast, movie_year);
  }
  return;
}

#endif //UNIONFIND_HPP
