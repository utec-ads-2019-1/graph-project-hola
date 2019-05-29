#ifndef EDGE_H
#define EDGE_H

#include "node.h"
#include <iostream>

template <typename G>
class Edge {
public:
    typedef typename G::E E;
    typedef typename G::node node;
    node* origin = nullptr;
    node* dest = nullptr;

    Edge(){data = 0; dir = false; origin = nullptr, dest = nullptr;}
    Edge(E value, node* orig, node* dst, bool direction) {data = value; origin = orig; dest = dst; dir = direction;}
    Edge(node* orig, node* dst) {origin = orig; dest = dst;}
    Edge(E value){data = value; dir = false;}
    Edge(E value, bool direction) {data = value; dir = direction;}

    E getData() {return data;}
    void setData(E newData) {data = newData;}
    bool getDir() { return dir;}
    void setDir(bool newDir) { dir = newDir;}
    node* getOrigin(){return origin;}
    node* getDest(){return dest;}

    Edge (E orig, E dst) {
      node* eOrig = new node(orig);
      node* eDest = new node(dst);

      origin = eOrig;
      dest = eDest;
    }
private:
    E data;
    bool dir;
};

#endif
