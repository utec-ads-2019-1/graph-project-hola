#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

#include "node.h"
#include "edge.h"

#include <iostream>

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

    Graph()
    {
        // TODO Constructor
    }

    ~Graph()
    {
        // TODO Destructor
    }

    void killself();

    int size()
    {
        return nodes.size();
    }


    bool insertNode(N name)
    {
        auto tempNode = this->getNode(name);
        if(tempNode != NULL)
        {
            if(tempNode->getData() == name)
                return false;
        }
        else
        {
            auto newNode = new node(name);
            nodes.push_back(newNode);
            return true;
        }
    }


    bool insertEdge(N orig, N dest, E height, bool direction=0)
    {
        auto firstNode = getNode(orig);
        auto secondNode = getNode(dest);
        if(firstNode == NULL || secondNode == NULL)
            return false;

        if(getEdge(orig, dest) != NULL)
        {
            return false;
        }
        else
        {
            auto newEdge = new edge(height);
            newEdge->nodes[0] = firstNode;
            newEdge->nodes[1] = secondNode;
            firstNode->edges.push_back(newEdge);
            return true;
        }
    }

    bool removeNode(N name)
    {
        auto tempNode = getNode(name);
        if(tempNode  == NULL )
            return false;
        nodes.erase();
        return true;
    }
    bool removeEdge(N orig, N dest)
    {
        auto tempEdge = getEdge(orig, dest);
        return true;
    }

    bool findEdge();
    bool findNode();

    bool density()
    {
        float dens = 0.0f;
        dens = 1/nodes.size()/(nodes.size()-1) ;

        return dens >= 0.6f;
    }
    bool grade(node a);
    bool connected();
    bool strongConnected();
    bool bipartite();

    void MST_Prim();
    void MST_Kruskal();

    void searchBFS();
    void searchDFS();

    void print()
    {
        for (ni = nodes.begin(); ni != nodes.end() ; ni++)
        {
            std::cout << (*ni)->getData() << " -> ";
            for (ei = (*ni)->edges.begin() ;  ei != (*ni)->edges.end(); ei++)
            {
                std::cout << (*ei)->getData() << "|" << (*ei)->nodes[1]-> getData() << " -> ";
            }
            std::cout << std::endl;
        }
    }


private:
    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;


    node *getNode(N name)
    {
        if(size()>0)
        {
            node *tempNode = nodes.front();
            for (ni = nodes.begin(); ni != nodes.end() ; ni++)
            {
                if((*ni)->getData() == name)
                    return *ni;
            }
            return NULL;
        }
        return NULL;
    }


    edge *getEdge(N orig, N dest)
    {
        if(size()>0)
        {
            for (ni = nodes.begin(); ni != nodes.end() ; ni++)
            {
                for (ei = (*ni)->edges.begin() ;  ei != (*ni)->edges.end(); ei++)
                {
                    if((*ei)->nodes[0]->getData() == orig && (*ei)->nodes[1]->getData() == dest)
                        return *ei;
                }
            }
        }
        return NULL;
    }

};

typedef Graph<Traits> graph;

#endif
