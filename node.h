#ifndef NODE_H
#define NODE_H

#include "edge.h"
#include <algorithm>
#include <list>

template <typename G>
class Node {
public:
    typedef typename G::N N;
    typedef typename G::E E;
    typedef typename G::edge edge;
    typedef typename G::EdgeSeq EdgeSeq;
    typedef std::list<edge*> Seq;

    EdgeSeq edges;

    Node(){}
    Node(N value){data = value; x = y = 0;}
    Node(N value, double xAxis, double yAxis){data = value; x= xAxis; y = yAxis;}

    N getData() {return data;}
    void setData(N newData) {data = newData;}

    double getX(){return x;}
    void setX(double X){x = X;}

    double getY(){return y;}
    void setY(double Y){y = Y;}
    
    void addEdge(edge* ed) {
      edges.push_back(ed);
    }

    edge* getMinEdge() {
      nodeEdges.sort([](edge* a, edge* b) {return a->getData() < b->getData();});
      return *nodeEdges.begin();
    }

private:
    N data = NULL;
    double x;
    double y;
    Seq nodeEdges;
};

#endif
