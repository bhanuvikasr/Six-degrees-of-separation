/*
 * ContactGraph.cpp
 * Author: Bhanu Vikas Renukuntla & Dion Chung
 * Date:   16th Nov 2016
 *
 * ContactGraph is a container for Person nodes for epidemic modeling
 */

#include <typeinfo>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include "ContactGraph.h"

using namespace std;

ContactGraph::ContactGraph(void) {}

/*
 * Loads data set and builds graph
 */
bool ContactGraph::loadFromFile(const char* in_filename) {
    // Initialize the file stream
    ifstream infile(in_filename);

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline( infile, s )) break;

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;

            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, ' ' )) break;

            record.push_back( next );
        }

        if (record.size() != 2) {
            // we should have exactly 2 columns
            continue;
        }

        string p1(record[0]);
        int person1_id = stoi(p1);
        string p2(record[1]);
        int person2_id = stoi(p2);

        Person* person1 = people_map[person1_id];
        if(person1 == nullptr){
          // create a Person node
          person1 = new Person(person1_id);
          people_map[person1_id] = person1;
        }

        Person* person2 = people_map[person2_id];
        if(person2 == nullptr){
          // create a second Person node
          person2 = new Person(person2_id);
          people_map[person2_id] = person2;
        }

        person1->contacts.push_back(person2);

    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/*
 * Infects friends with the virus based on rand() and infection_rate
 */
void ContactGraph::infect(Person* p, double infection_rate, int iterations) {
    queue<Person*> bfs_queue;
    queue<Person*> bfs_queue2;
    vector<int> counts;
    int time_value = 0;
    int infected_count = 1;

    p->isInfected = true;
    bfs_queue.push(p);


    while (!bfs_queue.empty()) {
      while (!bfs_queue.empty()) {
        Person* n = bfs_queue.front();
        bfs_queue.pop();
        bfs_queue2.push(n);

        if (n->isVisited) {
          continue;
        }
        else {
          n->isVisited = true;
        }

        for (int i=0; i<n->contacts.size(); i++) {
            Person* next = n->contacts[i];
            double p = ((double)rand() / RAND_MAX);
            bool getsInfected = p < infection_rate;
            if (getsInfected && !next->isInfected) {
              next->isInfected = getsInfected;
              infected_count++;
              bfs_queue2.push(next);
            }
        }
      }
      // perform swap with reset
      while (!bfs_queue2.empty()) {
        Person* n = bfs_queue2.front();
        bfs_queue2.pop();
        bool done = true;
        for (int i=0; i<n->contacts.size(); i++) {
          done = done & n->contacts[i]->isInfected;
        }
        if (!done) {
          n->isVisited = false;
          bfs_queue.push(n);
        }
      }
      time_value++;
      cout << time_value << " " << (double)infected_count * 100 /people_map.size() << " percent of population infected" << endl;
      iterations--;
      if (iterations==0){
        break;
      }
    }
}

/*
 * Resets graph for next run
 */
void ContactGraph::reset() {
  for (auto it = people_map.begin(); it != people_map.end(); ++it) {
    it->second->isInfected = false;
    it->second->isVisited = false;
  }
}

/* Destructor function
 *
 */
ContactGraph::~ContactGraph(){
  for (auto it = people_map.begin(); it != people_map.end(); ++it) {
    delete it->second;
  }
}
