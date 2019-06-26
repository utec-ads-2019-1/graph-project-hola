#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

#include "node.h"
#include "edge.h"

using namespace std;

class Traits {
	public:
		typedef char N;
		typedef int E;
};

template <typename Tr>
class Graph {
    public:
        typedef Graph<Tr> self;
        typedef Node<self> node;
        typedef Edge<self> edge;
        typedef vector<node*> NodeSeq;
        typedef list<edge*> EdgeSeq;
        typedef typename Tr::N N;
        typedef typename Tr::E E;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

        int nodesize = nodes.size();
        int edgesize = edgess.size();


    bool insertNode(N name, double xAxis = 0, double yAxis = 0) {
      auto tempNode = getNode(name);
      
      if(tempNode) return false;

      else {
        auto newNode = new node(name, xAxis, yAxis);
        nodes.push_back(newNode);
        return true;
      }
    }

    bool insertEdge(N orig, N dest, E weight=0, bool direction=0) {
        auto firstNode = getNode(orig);
        auto secondNode = getNode(dest);
        
        if(firstNode == nullptr || secondNode == nullptr) { return false;}

        else if(getEdge(orig, dest) != nullptr) return false;
  
        else {
          edge* newEdge = new edge(weight, firstNode, secondNode, direction);
          edgess.push_back(newEdge);
          firstNode->addEdge(newEdge);
          return true;
        }
    }

    node *getNode(N name) {
        auto *tmp = new node(name);

        if(nodes.size()>0) {
            ni = std::find_if(nodes.begin(), nodes.end(), [&tmp](node* x) {return x->getData() == tmp->getData();});
            if(ni != nodes.end())  return *ni;
            else return nullptr;
        }

        else return nullptr;
    }

    edge *getEdge(N orig, N dest) {

        edge* tmp = new edge(orig, dest);

        if(edgess.size() > 0) {
            ei = std::find_if(edgess.begin(), edgess.end(), [&tmp](edge* x) {
                return (x->getOrigin()->getData() == tmp->getOrigin()->getData()) && (x->getDest()->getData() == tmp->getDest()->getData());
            });
            if (ei != edgess.end()) return *ei;

            else return nullptr;
        }

        else return nullptr;
    }

    int getNumberEdges() {
        return edgess.size();
    }

    int getNumberNodes(){
        return nodes.size();
    }

    void print() {
        for (auto ei : edgess) {

            if(!ei->getDir())
                std::cout << ei->getOrigin()->getData() << " [" << ei->getData() << "] -> " << ei->getDest()->getData() << "\n";
            else
                std::cout << ei->getDest()->getData() << " [" << ei->getData() << "] -> " << ei->getOrigin()->getData() << "\n";

        }
    }

    Graph* 

    private:
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;
};

typedef Graph<Traits> graph;

#endif 