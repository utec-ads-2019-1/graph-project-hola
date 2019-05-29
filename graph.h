#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include "node.h"
#include "edge.h"
#include <algorithm>
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

    void killself()
    {
        // TODO
    }


    void createDS(self){
        for(auto ni : nodes){
            mapa.insert({ni->getData(),ni->getData() });
        }

        for(ei = edgess.begin(); ei != edgess.edn(); ei++){
            dsJoin(mapa, ei->origin, ei->dest);
        }
    }


    node* dsFind(map<N,N> &mapa, node* Nodo){
        N nodo = Nodo->getData();
        while(Nodo != mapa[Nodo]){
            mapa[Nodo] = mapa[mapa[Nodo]];
            Nodo = mapa[Nodo];
        }
        return Nodo;
    }


    void dsJoin(map<N,N> &mapa, node* n1, node* n2){
        N root1 = dsFind(mapa, n1);
        N root2 = dsFind(mapa, n2);
        mapa[root2] = root1;
    }

  /*  bool isConnected(){
        bool result = false;
        if(!mapa.empty()){
            N val = mapa.begin()->second;
            result = std::all_of(std::next(mapa.begin()),mapa.end(),[val](typename <insert map type>::const_reference t){return t->second == val;});
        }
        return result;
    }*/
    

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
          return true;
        }
    }

    bool removeNode(N name)
    {
        bool flag = false;
        NodeIte tempIte;

        if(nodes.size()<=0) return false;
        else
        {
            for (ni = nodes.begin(); ni != nodes.end() ; ni++)
            {
                for (ei = (*ni)->edges.begin() ;  ei != (*ni)->edges.end(); ei++)
                {
                    if((*ei)->nodes[1]->getData() == name)
                    {
                        (*ni)->edges.erase(ei);
                        break;
                    }
                }
                if((*ni)->getData() == name)
                {
                    flag = true;
                    tempIte = ni;
                }
            }
            if(!flag)
                return false;
            nodes.erase(tempIte);
            mapa.erase(tempIte);
            return true;
        }
    }

    bool removeEdge(N orig, N dest)
    {
        bool flag = false;

        if(nodes.size()>0)
        {
            for (ni = nodes.begin(); ni != nodes.end(); ni++)
            {
                for (ei = (*ni)->edges.begin() ;  ei != (*ni)->edges.end(); ei++)
                {
                    if((*ei)->nodes[0]->getData() == orig && (*ei)->nodes[1]->getData() == dest)
                    {
                        flag = true;
                        break;
                    }
                }
                if(flag == true) break;
            }
            if(!flag)
                return false;
            (*ni)->edges.erase(ei);
            return true;
        }
        return false;
    }


    bool findEdge(N orig, N dest)
    {
        if(!getEdge(orig, dest)) return false;
        else return true;
    }

    bool findNode(N name)
    {
        if(!getNode(name)) return false;
        else return true;
    }


    bool density() {
       float dens = 0.0f;

        dens = (float)getNumberEdges()/((float)nodes.size()*(float)(nodes.size()-1)) ;

        return dens >= 0.6f;
    }

    bool grade(node a);
    bool connected();
    bool strongConnected();
    bool bipartite();


    Graph* MST_Prim() {
      auto newGraph = new Graph;
      sort();

      int controller = 0;
      node* currentNode = getNode(edgess.front()->getOrigin()->getData());

      if (currentNode == nullptr) return nullptr;

      else {
       /* while (controller != nodes.size()) {
          
          } */

        return newGraph;

      }

   }


    void MST_Kruskal();

   /*  Graph* BFS(N orig)
    {
        auto newGraph = new Graph;

        for (ni = this->nodes.begin(); ni != this->nodes.end(); ni++)
            newGraph->insertNode((*ni)->getData(), (*ni)->getX(), (*ni)->getY());

        bool nodeVisited, destNodeVisited;

        queue<node *> container;
        list<node *> visited;

        auto currentNode = getNode(orig);
        auto prevNode = currentNode;

        if(currentNode == NULL)
            return NULL;
        else
        {
            container.push(currentNode);
            while(container.size()>0)
            {
                nodeVisited = false;
                prevNode = currentNode;
                currentNode = container.front();
                container.pop();
                for (auto it = visited.begin(); it != visited.end() ; it++)
                {
                    if(*it == currentNode)
                    {
                        nodeVisited = true;
                        break;
                    }
                }
                if(!nodeVisited)
                {
                    //cout << currentNode->getData() << ", ";

                    if(prevNode != currentNode)
                        newGraph->insertEdge(prevNode->getData(), currentNode->getData());

                    visited.push_back(currentNode);

                    for (ei = currentNode->edges.begin() ;  ei != currentNode->edges.end(); ei++)
                    {
                        destNodeVisited = 0;
                        for(auto it = visited.begin(); it != visited.end(); it++)
                        {
                            if((*ei)->nodes[1] == *it)
                            {
                                destNodeVisited = true;
                                break;
                            }
                        }
                        if(!destNodeVisited)
                        {
                            container.push((*ei)->nodes[1]);
                        }
                    }
                }
            }
            return newGraph;
        }
    }


    Graph* DFS(N orig)
    {
        auto newGraph = new Graph;

        for (ni = this->nodes.begin(); ni != this->nodes.end(); ni++)
            newGraph->insertNode((*ni)->getData(), (*ni)->getX(), (*ni)->getY());

        bool nodeVisited, destNodeVisited;

        stack<node *> container;
        list<node *> visited;

        auto currentNode = getNode(orig);
        auto prevNode = currentNode;

        if(currentNode == NULL)
            return NULL;
        else
        {
            container.push(currentNode);
            while(container.nodes.size()>0)
            {
                nodeVisited = false;
                prevNode = currentNode;
                currentNode = container.top();
                container.pop();
                for (auto it = visited.begin(); it != visited.end() ; it++)
                {
                    if(*it == currentNode)
                    {
                        nodeVisited = true;
                        break;
                    }
                }
                if(!nodeVisited)
                {
                    //cout << currentNode->getData() << ", ";

                    if(prevNode != currentNode)
                        newGraph->insertEdge(prevNode->getData(), currentNode->getData());


                    visited.push_back(currentNode);

                    for (ei = currentNode->edges.begin() ;  ei != currentNode->edges.end(); ei++)
                    {
                        destNodeVisited = 0;
                        for(auto it = visited.begin(); it != visited.end(); it++)
                        {
                            if((*ei)->nodes[1] == *it)
                            {
                                destNodeVisited = true;
                                break;
                            }
                        }
                        if(!destNodeVisited)
                        {
                            container.push((*ei)->nodes[1]);
                        }
                    }
                }
            }
            return newGraph;
        }
    } */

    void print() {
      for (auto ei : edgess) {
        std::cout << ei->getOrigin()->getData() << " [" << ei->getData() << "] -> " << ei->getDest()->getData() << "\n";
      }
    }


private:
    NodeSeq nodes;
    EdgeSeq edgess;
    NodeIte ni;
    EdgeIte ei;
    map<N,N> mapa; 

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


    void sort() {
      if (edgess.size() > 0) {
        edgess.sort([](edge* a, edge* b) {return a->getData() < b->getData();});
       }
    }
};

typedef Graph<Traits> graph;

#endif
