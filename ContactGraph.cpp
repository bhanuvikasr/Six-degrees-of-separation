/*
 * ContactGraph.cpp
 * Author: Bhanu Vikas Renukuntla & Dion Chung
 * Date:   16th Nov 2016
 *
 * ContactGraph is a container for Person nodes for epidemic modeling
 */

 #include <typeinfo>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ContactGraph.h"

using namespace std;

ContactGraph::ContactGraph(void) {}

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

void ContactGraph::infect(Person* p, float infection_rate, int iterations) {
    queue<Person*> bfs_queue;
    queue<Person*> bfs_queue2;
    vector<int> counts;

    bfs_queue.push(p);
    int dist = 0;
    int total_dist = 0;
    int total_persons = 0;

    r = ((double)rand() / RAND_MAX)

    while (!bfs_queue.empty()) {
      while (!bfs_queue.empty()) {
        Person* n = bfs_queue.front();
        bfs_queue.pop();
        bfs_queue2.push(n);

        if (n->isInfected) {
          continue;
        }
        else {
          n->isInfected = true;
          total_persons++;
          total_dist += dist;
          // cout << n->id << " ID " << total_persons << " p " << total_dist << " total dist " << endl;
        }

        for (int i=0; i<n->contacts.size(); i++) {
            Person* next = n->contacts[i];
            bfs_queue2.push(next);
        }
      }
      swap(bfs_queue, bfs_queue2);
      dist++;
    }
    return (float)total_dist/ total_persons;
}

void ContactGraph::reset() {
  for (auto it = people_map.begin(); it != people_map.end(); ++it) {
    it->second->isInfected = false;
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
