#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
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

    void killself()
    {
        // TODO
    }

    int nodes.size()
    {
        return nodes.nodes.size();
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
        for each node in self{              // modify
            mapa.insert({newNode,newNode});
        }

        for each edge in self{              // modify
            dsJoin origin and dest;
        }
    }

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

    bool insertEdge(N orig, N dest, E height=1, bool direction=0)
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

    Node* dsFind(map<node*,node*> &mapa, node* nodo){
        while(nodo != mapa[nodo]){
            mapa[nodo] = mapa[mapa[nodo]];
            nodo = mapa[nodo];
        }
        return nodo;
    }

    void dsJoin(mapa<node*,node*> &mapa, node* n1, node* n2){
        node* root1 = dsFind(mapa, n1);
        node* root2 = dsFind(mapa, n2);
        mapa[root1] = root2;
    }

    bool findEdge(N orig, N dest)
    {
        if(getEdge(orig, dest) == NULL) return false;
        else return true;
    }

    bool findNode(N name)
    {
        if(getNode(name) == NULL) return false;
        else return true;
    }

    bool density()
    {
        float dens = 0.0f;

        dens = (float)getNumberEdges()/(float)nodes.nodes.size()/(float)(nodes.nodes.size()-1) ;

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

    Graph* BFS(N orig)
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
            while(container.nodes.size()>0)
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
    }

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
    EdgeIte aei;
    map<node*,node*> mapa; 

    node *getNode(N name)
    {
        if(nodes.size()>0)
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
        if(nodes.size()>0)
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

    node *minEdge(N name)
    {
      if(nodes.size()>0)
      {
        for (ni = nodes.begin(); ni != nodes.end(); ni++)
        {
          if ((*ni)->getData() == name) {
            for (ei = (*ni)->edges.begin(); ei != (*ni)->edges.end() - 1; ei++){
              for (aei = (*ni)->edges.begin(); aei != (*ni)->edges.end() - ei - 1; aei ++) {
                if ((*aei)->getData() > (*ei)->getData() )
                  swap(*aei, *ei);
              }
            }
          }       
        }
      }
    }

    int getNumberEdges()
    {
        int count = 0;
        if(nodes.size()>0)
        {
            for (ni = nodes.begin(); ni != nodes.end() ; ni++)
            {
                count = count + (*ni)->edges.nodes.size();
            }
            return count;
        }
        return 0;
    }

};

typedef Graph<Traits> graph;

#endif
