/*
 * ActorGraph.cpp
 * Author: Bhanu Vikas Renukuntla & Dion Chung
 * Date:   16th Nov 2016
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

 #include <typeinfo>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"

using namespace std;

ActorGraph::ActorGraph(void) {}

/** You can modify this method definition as you wish
 *
 * Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
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

        ActorNode* actor = actors_map[actor_name];
        if(actor == nullptr){
          // create an actor node
          actor = new ActorNode(actor_name);
          actors_map[actor_name] = actor;
        }
        int weight = 2016 - movie_year;
        string movie_key = movie_title + to_string(weight);
        MovieNode<ActorNode>* movie = movies_map[movie_key];
        if(movie == NULL){
          // create a movie node
          if (movie_year < oldestYear) oldestYear = movie_year;
          movie = new MovieNode<ActorNode>(movie_title,weight);
          movies_map[movie_key] = movie;
        }
        actor->movies.push_back(movie);
        movie->cast.push_back(actor);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/* Destructor function
 *
 */
ActorGraph::~ActorGraph(){
  for (auto it = actors_map.begin(); it != actors_map.end(); ++it) {
    delete it->second;
  }
  for (auto it = movies_map.begin(); it != movies_map.end(); ++it) {
    delete it->second;
  }
}
