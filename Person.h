/**
* Person.h
* Author: Bhanu Vikas Renukuntla & Dion Chung
* Date:   16th Nov 2016
*
* A class, instances of which are Actor nodes stores the pointers to the movies
* of the actor
*/

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/** A class, instances of which are nodes are the edges in the graph.
 */
class Person{
public:
    int id;
    vector<Person*> contacts;
    bool isInfected;

    Person(int id);

    // bool operator<(const ActorNode& other);

};

#endif // PERSON_H
