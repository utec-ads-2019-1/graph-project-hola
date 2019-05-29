#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
public:
    typedef typename G::E E;
    typedef typename G::node node;
    node* origin = nullptr;
    node* dest = nullptr;

    Edge(){data = 0; dir = false;}
    Edge(E value, node* origin, node* dest, bool direction) {origin = origin; dest = dest; data = value; dir = direction;}
    Edge(node* origin, node* dest) {origin = origin; dest = dest;}
    Edge(E value){data = value; dir = false;}
    Edge(E value, bool direction) {data = value; dir = direction;}

    E getData() {return data;}
    void setData(E newData) {data = newData;}
    bool getDir() { return dir;}
    void setDir(bool newDir) { dir = newDir;}

private:
    E data;
    bool dir;
};

#endif
