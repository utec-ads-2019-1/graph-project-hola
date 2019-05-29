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

    void sort (vector<node*> &Nodes, int left, int right) {
      if (left >= right) return;
      int pivot = Nodes[left + (right - left)/2]->edges->getData();
      int lindex = left - 1;
      int rindex = right + 1;

      while(1) {
        while(Nodes[++rindex]->edges->getData() < pivot);
        while(Nodes[--rindex]->edges->getData() > pivot);
        if(lindex >= rindex) break;
        swap (Nodes[lindex], Nodes[rindex]);
      }

      sort(Nodes, left, rindex);
      sort(Nodes, rindex + 1, right);
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


    bool insertNode(N name, double xAxis = 0, double yAxis = 0)
    {
      auto tempNode = this->getNode(name);
        if(tempNode != NULL)
        {
            if(tempNode->getData() == name)
                return false;
        }
        else
        {
            auto newNode = new node(name, xAxis, yAxis);
            nodes.push_back(newNode);
            return true;
        }
    }

    bool insertEdge(N orig, N dest, E weight=0, bool direction=0) {
        auto firstNode = getNode(orig);
        auto secondNode = getNode(dest);
        if(firstNode == NULL || secondNode == NULL) return false;

        if(getEdge(orig, dest) != NULL) return false;

        else {
          auto newEdge = new edge(weight, firstNode, secondNode, direction);
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
        if(getEdge(orig, dest) == NULL) return false;
        else return true;
    }

    bool findNode(N name)
    {
        if(!getNode(name)) return false;
        else return true;
    }

    bool density()
    {
        float dens = 0.0f;

        dens = (float)getNumberEdges()/(float)nodes.size()/(float)(nodes.size()-1) ;

        return dens >= 0.6f;
    }

    bool grade(node a);
    bool connected();
    bool strongConnected();
    bool bipartite();


    Graph* MST_Prim(N orig)
    {
      auto newGraph = new Graph;

      for (ni = this->nodes.begin(); ni != this->nodes.end(); ni++)
            newGraph->insertNode((*ni)->getData(), (*ni)->getX(), (*ni)->getY());

      int controller = 0;
      auto currentNode = getNode(orig);

      if (currentNode == NULL)
        return NULL;

      else
      {
        while (controller != nodes.size()) {

          }

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
        if(ni != nodes.end()){
            return *ni;
        }else{
            return nullptr;
        }
       }else{
        return nullptr;
       }
    }


    edge *getEdge(N orig, N dest) {

      if(edgess.size() > 0) {
        auto origNode = getNode(orig);
        auto destNode = getNode(dest);
        if(origNode == NULL || destNode == NULL) return NULL;

        for (ei = (*ni)->edges.begin() ;  ei != (*ni)->edges.end(); ei++)
        {
          if((*ei)->getOrigin()->getData() == orig && (*ei)->getDest()->getData() == dest)
              return *ei;
        }

        return *ei;
      }
    }


    int getNumberEdges() {
      return edgess.size();
    }

/*
    void sort() {
      if (edgess.size() > 0) {
        edgess.sort([](edge* a, edgess* b) {return a->getData() < b->getData()});
      }
    }
*/
};

typedef Graph<Traits> graph;

#endif
