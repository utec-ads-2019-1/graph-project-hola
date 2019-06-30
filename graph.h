#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include "node.h"
#include "edge.h"
#include "read.h"
#include <algorithm>
#include <limits>
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

    Graph(int n) {
			size = n;
			create_matrix(size);
    }

		Graph(string txt)	{
			new Read<Tr>(txt);
		}

		Graph() {
		}

    ~Graph()
    {
        // TODO Destructor
    }

    void killself()
    {
        // TODO
    }
		

		int getNodePos(N name) {
			int counter = 0;
			for (auto ni : nodes) {
				if ((*ni).getData() == name) {
					return counter;
				}
				counter ++;
			}

			return -1;
		}


		void create_matrix(int size) {
			edges_matrix = new int *[size];
			
			for (int i = 0; i < size; i++) {
				edges_matrix[i] = new int [size];
				for (int j = 0; j < size; j++) {
					if (i == j) edges_matrix[i][j] = 0;
					else edges_matrix[i][j] = std::numeric_limits<int>::max();
				}
			}		
		}


		void Floyd_Warshall() {
			int **fw = edges_matrix;

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					for (int k = 0; k < size; k++) {
						if (fw[j][i] == std::numeric_limits<int>::max() || fw[i][k] == std::numeric_limits<int>::max())
						continue;

						else {
							if ((fw[j][i] + fw[i][k]) < fw[j][k]) 
								fw[j][k] = fw[j][i] + fw[i][k];
						}
					}
				}
			}
			
			print_matrix(fw);		
		}


		void print_matrix(int** matrix) {
			std::cout << '\n';

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (matrix[i][j] == std::numeric_limits<int>::max())
						std::cout << "inf ";
					else std::cout << matrix[i][j] << ' ';
				}
				std::cout << '\n';
			}
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


    bool insertNode(N name, double xAxis = 0, double yAxis = 0, bool reached = 0) {
      auto tempNode = getNode(name);

      if(tempNode) return false;

      else {
        auto newNode = new node(name, xAxis, yAxis, reached);
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

					if (direction == 0) edges_matrix[getNodePos(dest)][getNodePos(orig)] = weight;
					edges_matrix[getNodePos(orig)][getNodePos(dest)] = weight;
					
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


    bool findEdge(N orig, N dest) {
        if(!getEdge(orig, dest)) return false;
        else return true;
    }


    bool findNode(N name) {
        if(!getNode(name)) return false;
        else return true;
    }


    bool isDense(float threshold = 0.6) {
        float dens = 0.0f;
        dens = (float)getNumberEdges()/((float)nodes.size()*(float)(nodes.size()-1)) ;
        return dens >= threshold;
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

        stack<node *> container;

        for (ni = this->nodes.begin(); ni != this->nodes.end(); ni++)
        {
            newGraph->insertNode((*ni)->getData(), (*ni)->getX(), (*ni)->getY());
            (*ni)->setReached(0);
        }

        auto currentNode = getNode(orig);

        if(currentNode == NULL)
            return NULL;
        else
        {
            container.push(currentNode);
            while(container.size()>0)
            {
                bool flag = 0;
                currentNode = container.top();

                if(!currentNode->getReached()) {
                    currentNode->setReached(1);
                }
                for(auto ei : currentNode->getEdgeVector())
                {
                    if(!ei->getDest()->getReached())
                    {
                        container.push(ei->getDest());
                        flag = 1;
                        break;
                    }
                }
                if(!flag)
                {
                    container.pop();
                }
                else
                {
                    if(currentNode != container.top())
                    {
                        auto tempEdge = getEdge(currentNode->getData(),container.top()->getData());
                        if(tempEdge != NULL)
                            newGraph->insertEdge(tempEdge->getOrigin()->getData(), tempEdge->getDest()->getData(), tempEdge->getData());
                    }
                }
            }
            return newGraph;
        }
    }


    bool StronglyConnected()
    {
        auto tempGraph = DFS('B');
        auto localSCC = transpose()->DFS('B');

        return(localSCC->getNumberEdges() == this->getNumberEdges());
    }



    void print() {
        for (auto ei : edgess) {

            if(!ei->getDir())
                std::cout << ei->getOrigin()->getData() << " [" << ei->getData() << "] -> " << ei->getDest()->getData() << "\n";
            else
                std::cout << ei->getDest()->getData() << " [" << ei->getData() << "] -> " << ei->getOrigin()->getData() << "\n";

        }
    }

    void print2(){
        for(auto ni : nodes)
        {
            printf("\nNodo %c: ", ni->getData());
            for(auto ei : ni->getEdgeVector())
            {
                printf("[%2d -> %c] ", ei->getData(), ei->getDest()->getData());
            }
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


    void sort() {
        if (edgess.size() > 0) {
            edgess.sort([](edge* a, edge* b) {return a->getData() < b->getData();});
        }
    }

    Graph* transpose()
    {
        auto newGraph = new Graph;

        for (auto ni : nodes)
        {
            newGraph->insertNode(ni->getData(), ni->getX(), ni->getY());
            ni->setReached(0);
        }
        for (auto ei : edgess)
        {
            newGraph->insertEdge(ei->getDest()->getData(), ei->getOrigin()->getData(), ei->getData());
        }

        return newGraph;
    }


private:
    NodeSeq nodes;
    EdgeSeq edgess;
    NodeIte ni;
    EdgeIte ei;
    map<N,N> mapa;
		int **edges_matrix;
		int size;

};

typedef Graph<Traits> graph;

#endif
