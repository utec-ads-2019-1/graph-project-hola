#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
public:
    typedef typename G::E E;
    typedef typename G::node node;
    node* origin;
    node* dest;

    Edge(){data = 0; dir = false;}
    Edge(E value, node* orig, node* des, bool direction) {origin = orig; dest = des; data = value; dir = direction;}
    Edge(node* orig, node* des) {origin = orig; dest = des;}
    Edge(E value){data = value; dir = false;}
    Edge(E value, bool direction) {data = value; dir = direction;}

    E getData() {return data;}
    void setData(E newData) {data = newData;}
    bool getDir() { return dir;}
    void setDir(bool newDir) { dir = newDir;}
    node* getOrigin(){return origin;}
    node* getDest(){return dest;}
private:
    E data;
    bool dir;
};

#endif
