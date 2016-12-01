/**
* Person.cpp
* Author: Bhanu Vikas Renukuntla & Dion Chung
* Date:   16th Nov 2016
*
* A class, instances of which are people nodes stores the pointers to their
* contacts as well as boolean if infected.
*/
#include "Person.h"
#include <vector>


// method for creating and initialising a node
Person::Person(int id) : id(id), isInfected(false), isVisited(false) {}
