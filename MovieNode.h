/*
 * MovieNode.h
 * Author: Bhanu Vikas Renukuntla & Dion Chung
 * Date:   16th Nov 2016
 *
 * This file is a header file for the class Movie Node
 */

#ifndef MOVIENODE_H
#define MOVIENODE_H

#include <iostream>
#include <string>
#include <vector>


typedef unsigned char byte;

using namespace std;

/** A class, instances of which are movie nodes stores the pointers to the cast
    of the movie
 */
template<typename Data>
class MovieNode {

public:
    string name;
    int weight;
    vector<Data*> cast;

    MovieNode(string name,
    int weight)
        : name(name), weight(weight) { }

};



#endif // MOVIENODE_H
