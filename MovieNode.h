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
class MovieNode {

public:
    string name;
    int weight;
    vector<ActorNode*> cast;
    // vector<int> cast;

    MovieNode(string name,
    int weight,
    // vector<int> cast)
    vector<ActorNode*> cast)
        : name(name), weight(weight) { }
    //~MovieNode();
    bool Add_cast(ActorNode* new_cast);
    // bool Add_cast(int new_cast);

};



#endif // MOVIENODE_H
