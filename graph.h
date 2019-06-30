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


    N dsFind(N Nodo){
        while(Nodo != mapa[Nodo]){
            mapa[Nodo] = mapa[mapa[Nodo]];
            Nodo = mapa[Nodo];
        }
        return Nodo;
    }


    void dsJoin(N n1, N n2){
        N root1 = dsFind(n1);
        N root2 = dsFind(n2);
        mapa[root2] = root1;
    }


    bool insertNode(N name, double xAxis = 0, double yAxis = 0) {
      auto tempNode = getNode(name);
      
      if(tempNode) return false;

      else {
        auto newNode = new node(name, xAxis, yAxis);
        nodes.push_back(newNode);
        mapa.insert({name,name});
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
          dsJoin(orig, dest);
          return true;
        }
    }


    bool removeNode(N name) {
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

    bool density() {
      float dens = 0.0f;

       dens = (float)getNumberEdges()/((float)nodes.size()*(float)(nodes.size()-1)) ;
       
       return dens >= 0.6f;
    }

    int grade(node* currNode) {
        int temp;
        for (ei = edgess.begin() ;  ei != edgess.end(); ei++)
        {
            if( (*ei)->getOrigin() == currNode || (*ei)->getDest() == currNode ())
            {
                temp++;
            }
        }
        return temp;
    }


    bool connected(){
        bool flag = true;

                for(ni = nodes.begin(); ni != nodes.end(); ni++)
                {
                    for (ei = edgess.begin() ;  ei != edgess.end(); ei++)
                    {
                        if( (*ei)->getOrigin() == (*ni) || (*ei)->getDest() == (*ni) )
                        {
                            flag = true;
                            break;
                        }
                        else
                        {
                            flag = false;
                        }
                    }
                    if(!flag)
                        break;
                }
                return flag;
    }
    
    
    bool bipartite(){
        map<char,char> color;
        queue<node*> q;
        auto firstNode = *(nodes.begin());
        q.push(firstNode);
        color.insert({firstNode->getData(),'R'});
        while(!q.empty()){
            node* current = q.front();
            vector<char> adj = current->adjacentNodes();
            if(color[current->getData()] == 'R'){
                for(int i = 0;i<adj.size();i++){
                    if(color[adj[i]] == 'R'){
                        return false;
                    }
                    color[adj[i]] = 'B';
                    q.push(getNode(adj[i]));
                }
            }
            if(color[current->getData()] == 'B'){
                for(int i = 0;i<adj.size();i++){
                    if(color[adj[i]] == 'B'){
                        return false;
                    }
                    color[adj[i]] = 'R';
                    q.push(getNode(adj[i]));
                }                
            }
        q.pop();
        }
        return true;
    }   


    Graph* MST_Prim() {
      if (!connected()) return nullptr;
      auto newGraph = new Graph;

      node* currentNode = getNode(edgess.front()->getOrigin()->getData());

      if (currentNode == nullptr) return nullptr;

      else {
        for(auto ni : nodes) {
          if (!ni->getMinEdge()) ni++;
         
          else {
            auto o = ni->getMinEdge()->getOrigin();
            auto d = ni->getMinEdge()->getDest();

            newGraph->insertNode(o->getData(), o->getX(), o->getY(), 1);

            cout << o->getData() << "->" <<  d->getData() << "[" <<  ni->getMinEdge()->getData() << "] " << "\n";
            newGraph->insertEdge(o->getData(), d->getData(), ni->getMinEdge()->getData(), ni->getMinEdge()->getDir());
            ni->setReached(1);
          }
       }

           return newGraph;
       }

    }


    Graph* MST_Kruskal(){
        auto newGraph = new Graph;

        sort();
        for(auto ni : nodes){
            newGraph->insertNode(ni->getData(), ni->getX(),ni->getY());
        }
        for(auto ei : edgess){
            N o = ei->getOrigin()->getData();
            N d = ei->getDest()->getData();
            if(newGraph->dsFind(o) != newGraph->dsFind(d))
                newGraph->insertEdge(o,d,ei->getData(), ei->getDir());
        }
        return newGraph;
    }    


    Graph* BFS(N orig) {
      auto newGraph = new Graph;

      for (ni = this->nodes.begin(); ni != this->nodes.end(); ni++) {
        newGraph->insertNode((*ni)->getData(), (*ni)->getX(), (*ni)->getY());
        (*ni)->setReached(0);
      }

      queue<node *> container;

      auto currentNode = getNode(orig);
      auto prevNode = currentNode;

      if(currentNode == NULL) return NULL;
       
      else {
        container.push(currentNode);
        
        while(container.size()>0) {
        //prevNode = currentNode;
        currentNode = container.front();
        container.pop();

        for (ei = edgess.begin() ;  ei != edgess.end(); ei++) {
          if( (*ei)->getDest() == currentNode && ((*ei)->getOrigin()->getReached())) {
            prevNode = (*ei)->getOrigin();
            break;
          }
        }

                if(prevNode == NULL)
                    prevNode = currentNode;


                if(!currentNode->getReached())
                {
                    //cout << currentNode->getData() << ", ";

                    if(prevNode != currentNode)
                    {
                        auto tempEdge = getEdge(prevNode->getData(),currentNode->getData());
                        newGraph->insertEdge(prevNode->getData(), currentNode->getData(), tempEdge->getData());
                    }


                    currentNode->setReached(1);

                    for (ei = edgess.begin() ;  ei != edgess.end(); ei++)
                    {
                        if( (*ei)->getOrigin() == currentNode && (!(*ei)->getDest()->getReached()))
                        {
                            container.push((*ei)->getDest());
                        }
                    }
                }
            }
            return newGraph;
        }

    }


    Graph* DFS(N orig){
        auto newGraph = new Graph;

        for (ni = this->nodes.begin(); ni != this->nodes.end(); ni++)
        {
            newGraph->insertNode((*ni)->getData(), (*ni)->getX(), (*ni)->getY());
            (*ni)->setReached(0);
        }


        bool nodeVisited, destNodeVisited;

        stack<node *> container;

        auto currentNode = getNode(orig);

        if(currentNode == NULL)
            return NULL;
        else
        {
            container.push(currentNode);
            while(container.size()>0)
            {
                currentNode = container.top();
                container.pop();

                if(!currentNode->getReached())
                {
                    currentNode->setReached(1);

                    for (ei = edgess.begin() ;  ei != edgess.end(); ei++)
                    {
                        if (!(*ei)->getDir())
                        {
                            if( (*ei)->getOrigin() == currentNode && (!(*ei)->getDest()->getReached()))
                            {
                                container.push((*ei)->getDest());
                                break;
                            }
                        }
                        else
                        {
                            if( (*ei)->getDest() == currentNode && (!(*ei)->getOrigin()->getReached()))
                            {
                                container.push((*ei)->getOrigin());
                                break;
                            }
                        }
                    }

                    if(!container.empty())
                    {
                        if(currentNode != container.top())
                        {
                            if (!(*ei)->getDir())
                            {
                                auto tempEdge = getEdge(currentNode->getData(),container.top()->getData());
                                newGraph->insertEdge(tempEdge->getOrigin()->getData(), tempEdge->getDest()->getData(), tempEdge->getData());
                            }
                            else
                            {
                                auto tempEdge = getEdgeDir(currentNode->getData(),container.top()->getData());
                                newGraph->insertEdge(tempEdge->getOrigin()->getData(), tempEdge->getDest()->getData(), tempEdge->getData());
                            }

                        }

                    }

                }
            }
            return newGraph;
        }
    }


    bool StronglyConnected()
    {
        auto tempGraph = DFS('B');

        stack<node *> container = stackSCC(tempGraph);

        transpose();

        auto topStack = container.top();
        container.pop();

        auto localSCC = DFS(topStack->getData());

        if(localSCC->getNumberEdges() == this->getNumberEdges())
            return true;

        return false;

    }

    //////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////SEGUNDA ENTREGA////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    Graph* Dijkstra(N a){

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

    edge* getEdgeDir(N orig, N dest) {

        edge* tmp = new edge(orig, dest);

        if(edgess.size() > 0) {

            ei = std::find_if(edgess.begin(), edgess.end(), [&tmp](edge* x) {
                return (x->getDest()->getData() == tmp->getOrigin()->getData()) && (x->getOrigin()->getData() == tmp->getDest()->getData());
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

    void sort() {
        if (edgess.size() > 0) {
            edgess.sort([](edge* a, edge* b) {return a->getData() < b->getData();});
        }
    }

    void transpose()
    {
        for (ei = edgess.begin() ;  ei != edgess.end(); ++ei)
            (*ei)->setDir(1);
    }


    stack<node*> stackSCC(Graph* graphDFS)
    {
        stack<node *> container;

        for (ni = graphDFS->nodes.begin(); ni != graphDFS->nodes.end(); ni++)
            (*ni)->setReached(0);

        for (ei = graphDFS->edgess.begin() ;  ei != graphDFS->edgess.end(); ei++)
        {
            if( (!(*ei)->getOrigin()->getReached()))
            {
                container.push((*ei)->getOrigin());
                (*ei)->getOrigin()->setReached(1);
            }

            if (!(*ei)->getDest()->getReached())
            {
                container.push((*ei)->getDest());
                (*ei)->getDest()->setReached(1);
            }

        }

        return container;
    }

};

typedef Graph<Traits> graph;

#endif
