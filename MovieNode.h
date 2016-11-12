#ifndef MOVIENODE_H
#define MOVIENODE_H

#include <iostream>
#include <string>
#include <vector>
// #include "ActorNode.h"


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
    int weight,
    vector<Data*> cast)
        : name(name), weight(weight) { }

    bool addCast(Data* new_cast);

};



#endif // MOVIENODE_H
