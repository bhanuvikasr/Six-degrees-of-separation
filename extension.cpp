/*
 * extension.cpp
 * Author: Bhanu Vikas Renukuntla & Dion Chung
 * Date:   16th Nov 2016
 *
 * This file runs simulations over epidemic models
 */

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
#include "Person.h"
#include "ContactGraph.h"


using namespace std;

float getAvgBaconNumber(Person* p, ContactGraph& G) {
  queue<Person*> bfs_queue;
  queue<Person*> bfs_queue2;
  vector<int> counts;

  bfs_queue.push(p);
  int dist = 0;
  int total_dist = 0;
  int total_persons = 0;

  while (!bfs_queue.empty()) {
    while (!bfs_queue.empty()) {
      Person* n = bfs_queue.front();
      bfs_queue.pop();
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

/** MAIN function
 */
int main(int argc, char**argv){
  char* const connections = argv[1];
  // int patient_zero = atoi(argv[2]);
  string rate = argv[2];
  float infection_rate = (float)stoi(rate);

  // configuration constants
  int iterations = 100;
  int total_people = 10000; // can be approx, defines range for connectedness search

  // istream In;
  ContactGraph G;
  G.loadFromFile(connections);
  Person* p = NULL;
  // cout << "This is the person " << p->id << endl;

  // get smallest average Bacon number and largest from 100 random entries
  float max = 0;
  Person* max_p = NULL;
  float min = total_people;
  Person* min_p = NULL;

  for (int i=0; i< 100; i++) {
    int random_p = rand() % total_people;
    cout << "Random p " << random_p << endl;
    p = G.people_map[random_p];
    float baconNumber = getAvgBaconNumber(p, G);
    G.reset();

    if (baconNumber > max) {
      max = baconNumber;
      max_p = p;
    }

    if (baconNumber < min) {
      min = baconNumber;
      min_p = p;
    }
  }
  cout << "Max " << max << " with " << max_p->id << endl;
  cout << "Min " << min << " with " << min_p->id << endl;

  // infect the least connected Person
  G.infect(min_p, infection_rate, iterations);
  G.reset();

  // infect the most connected Person
  G.infect(max_p, infection_rate, iterations);
  G.reset();
}
