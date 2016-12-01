/*
 * extension.cpp
 * Author: Bhanu Vikas Renukuntla & Dion Chung
 * Date:   16th Nov 2016
 *
 * This file runs simulations over epidemic models
 */

#include <ctime>
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
      if (n->isVisited) {
        continue;
      }
      else {
        n->isVisited = true;
        total_persons++;
        total_dist += dist;
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
  string rate = argv[2];
  // implies min infection_rate 0.000001, but that's no fun
  double infection_rate = stod(rate);
  int iterations = stoi(argv[3]);

  // configuration constants, number of people to sample for min and max
  int rangeSet = 100;

  ContactGraph G;
  G.loadFromFile(connections);
  Person* p = NULL;
  srand (time(NULL));

  // get smallest average Bacon number and largest from 100 random entries
  int total_people = G.people_map.size();
  float max = 0;
  Person* max_p = NULL;
  float min = total_people;
  Person* min_p = NULL;

  for (int i=0; i< rangeSet; i++) {
    int random_p = rand() % total_people;
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

  // infect the most connected Person, smallest average bacon number
  cout << "Infecting " << min_p->id << " with average Bacon Number " << min << endl;
  G.infect(min_p, infection_rate, iterations);
  G.reset();

  // infect the least connected Person, largest average bacon number
  cout << "Infecting " << max_p->id << " with average Bacon Number " << max << endl;
  G.infect(max_p, infection_rate, iterations);
  G.reset();
}
