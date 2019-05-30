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
    typedef typename EdgeSeq::iterator EdgeIte;
    EdgeSeq edges;
    EdgeIte nie;

    Node(){}
    Node(N value){data = value; x = y = reached = 0;}
    Node(N value, double xAxis, double yAxis, bool r){data = value; x= xAxis; y = yAxis; reached = r;}

    N getData() {return data;}
    void setData(N newData) {data = newData;}

    double getX(){return x;}
    void setX(double X){x = X;}

    double getY(){return y;}
    void setY(double Y){y = Y;}

    bool getReached(){return reached;}
    void setReached(bool R){reached = R;}
    
    void addEdge(edge* ed) {
      nodeEdges.push_back(ed);
    }

    edge* getMinEdge() {
      nodeEdges.sort([](edge* a, edge* b) {return a->getData() < b->getData();});

      if (nodeEdges.front()->getDest()->getReached()) return *std::next(nodeEdges.begin());
      else return *nodeEdges.begin();

    }

    std::vector<char> adjacentNodes(){
        std::vector<char> adj;
        for(auto ei : nodeEdges){
            adj.push_back(ei->getData());
        }
        return adj;
    }

private:
    N data = NULL;
    double x;
    double y;
    bool reached;
    Seq nodeEdges;
};

#endif
