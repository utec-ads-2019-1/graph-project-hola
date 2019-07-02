#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <math.h>
#include "node.h"
#include "edge.h"
//#include "read.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <limits>
#include <iostream>

#define WINDOW 950
#define REAL_RADIUS 1
#define RADIUS REAL_RADIUS * 0.05
#define NORM 0.05

using namespace std;

class Traits {
public:
    typedef char N;
    typedef int E;
		typedef string R;
};

template <typename Tr>
class Graph {
public:
    typedef Graph<Tr> self;
    typedef Node<self> node;
    typedef Edge<self> edge;
		typedef Read<self> read;
    typedef vector<node*> NodeSeq;
    typedef list<edge*> EdgeSeq;
    typedef typename Tr::N N;
    typedef typename Tr::E E;
		typedef typename Tr::R R;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;

    /////////////////////////////////////////////////////////////////
    ///////////////////////OPENGL////////////////////////////////////
    void drawGraph() {
        vector<edge*> drawn;
        for (auto ei : edgess) {
            node* origin = ei->getOrigin();
            node* dest = ei->getDest();
            float fX = origin->getX();
            float fY = origin->getY();
            float sX = dest->getX();
            float sY = dest->getY();

            if(std::count(drawn.begin(),drawn.end(),ei) == 0){
                if(ei->getDir()){
                    if(getEdge(dest->getData(),origin->getData()) != nullptr && (getEdge(dest->getData(),origin->getData()))->getDir()){
    				    //drawTwoLines

                        drawn.push_back(getEdge(dest->getData(),origin->getData()));
                    }
    				else{
                        drawArrow(ei->getData(),fX,fY,sX,sY);
                    }
                }
                else{
                    drawLine(ei->getData(),fX,fY,sX,sY);
                }
                drawn.push_back(ei);
            }
        }

        for (auto ni : nodes){
            N name = ni->getData();
            float nX = ni->getX();
            float nY = ni->getY();
            drawCircle(name,nX,nY);
        }
    }

    string int_string(int n){
        string str;
        while(n){
            str.push_back(n%10 + 48);
            n = n/10;
        }
        reverse(str.begin(), str.end());
        return str;
    }
	void write(double x, double y, int weight) {
		GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
		string str = int_string(weight);
		glRasterPos2f(x, y);
		for (size_t i = 0; i < str.size(); i++) {
			glutBitmapCharacter(font_style, str[i]);
		}
	}

    void drawArrow(int weight,double x1, double y1, double x2, double y2) {
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(4.0);

        //Normalizar
        x1 *= NORM;
        y1 *= NORM;
        x2 *= NORM;
        y2 *= NORM;

        glBegin(GL_LINES);
        glColor4f(255.0, 255.0, 255.0, 1.0);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();

        double vx = x1 - x2;                        //variacion
        double vy = y1 - y2;                        //variacion
        double d = sqrt(vx*vx + vy * vy);           //Modulo
        double s = 1.0f / d;                        //Vector unitario
        double r = (d - RADIUS) / d;                //Ratio
        double newX = ((1 - r)*x1 + r * x2);
        double newY = ((1 - r)*y1 + r * y2);
        vx *= s;
        vy *= s;

        //normalizar
        vx *= NORM;
        vy *= NORM;

        double size = 0.5;

        glBegin(GL_LINES);
        glColor4f(255.0, 255.0, 255.0, 1.0);
        glVertex2f(newX, newY);
        glVertex2f(newX + size * (vx + vy), newY + size * (vy - vx));
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(newX, newY);
        glVertex2f(newX + size * (vx - vy), newY + size * (vy + vx));
        glEnd();
        float yW = (y1 + y2) / 2;
        float xW = (x1 + x2) / 2;
		double var = 0.003;
		glColor3f(0.0, 0.0, 1.0);
		write(xW + var, yW, weight);
		write(xW, yW + var, weight);
		write(xW - var, yW, weight);
		write(xW, yW - var, weight);
		write(xW + var / 2, yW, weight);
		write(xW - var / 2, yW, weight);
		write(xW, yW + var / 2, weight);
		write(xW, yW - var / 2, weight);
		glColor3f(255.0, 255.0, 255.0);
		write(xW, yW, weight);
    }
    void drawLine(int weight, double x1, double y1, double x2, double y2) {
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(1.0);
        x1 *= NORM;
        y1 *= NORM;
        x2 *= NORM;
        y2 *= NORM;
        glBegin(GL_LINES);
        glColor4f(255.0, 255.0, 255.0, 1.0);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
		float yW = (y1 + y2) / 2;
		float xW = (x1 + x2) / 2;
		double var = 0.002;
		glColor3f(0.0, 0.0, 1.0);
		write(xW + var, yW, weight);
		write(xW, yW + var, weight);
		write(xW - var, yW, weight);
		write(xW, yW - var, weight);
		write(xW + var / 2, yW, weight);
		write(xW - var / 2, yW, weight);
		write(xW, yW + var / 2, weight);
		write(xW, yW - var / 2, weight);
		glColor3f(255.0, 255.0, 255.0);
		write(xW, yW, weight);
    }
    void drawCircle(char C, double x, double y) {
        double y0 = y - RADIUS / 2;
        double x0 = x - RADIUS / 2;
        x0 *= NORM;
        y0 *= NORM;
        x *= NORM;
        y *= NORM;
        int i;
        float triangleAmount = 1000.0f;
        float twicePi = 2.0f * M_PI;
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(1.0);
        glBegin(GL_LINES);
        glColor4f(0.0, 0.0, 255.0, 1.0);
        for (i = 0; i <= triangleAmount; i++)
        {
            glVertex2f(x, y);
            float norm_x = x + (RADIUS * cos(i * twicePi / triangleAmount));
            float norm_y = y + (RADIUS * sin(i * twicePi / triangleAmount));

            glVertex2f(norm_x, norm_y);
        }
		glBegin(GL_LINES);
		glColor4f(255.0, 255.0, 255.0, 1.0);
		for (i = 0; i <= triangleAmount; i++)
		{
			glVertex2f(x, y);
			float norm_x = x + ((RADIUS-0.004) * cos(i * twicePi / triangleAmount));
			float norm_y = y + ((RADIUS - 0.004) * sin(i * twicePi / triangleAmount));

			glVertex2f(norm_x, norm_y);
		}
        glEnd();
        glColor3f(0.0, 0.0, 0.0);
        GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
        x0 = x0 - 0.011;
        y0 = y0 - 0.01;
        glRasterPos2f(x0, y0);
        glutBitmapCharacter(font_style, C);
    }

    /////////////////////////////////////////////////////////////////
    ///////////////////////OPENGL////////////////////////////////////


    Graph(int n) {
			size = n;
			create_matrix(size);
    }

		Graph(string txt)	{
			new Read<Tr>(txt);
		}

		Graph() {
			size = 0;
			create_matrix(0);
			direction = 0;
		}

    ~Graph()
    {
        // TODO Destructor
    }

    void killself()
    {
        // TODO
    }

		void setSize(int n) { size = n; create_matrix(n); }
		
		void setDirected(bool n) { direction = n; }
		

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
			
			print_matrix(fw, "Floyd Warshall");		
		}


		void print_matrix(int** matrix, string name) {
			std::cout << "\n";
			std::cout << "\n-----------------\n" <<
									 name  <<
									 "\n-----------------\n";

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


    bool insertEdge(N orig, N dest, E weight=0) {
				
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

    //////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////SEGUNDA ENTREGA////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    Graph* Dijkstra(N a){
		int index;
        auto newGraph = new Graph(size);
        for(int i=0;i<size;i++){
            if(nodes[i]->getData() == a){
                index = i;
				break;
            }
        }
        int* dist = new int[size];
        bool* set = new bool[size];
		int* parent = new int[size];

        for(int i = 0;i<size;i++){
            dist[i] = std::numeric_limits<int>::max();
			set[i] = false;
			parent[i] = i;
        }
        dist[index] = 0;

        for(int i = 0; i<size-1;i++){
            int u = minDist(dist,set);
            set[u] = true;
            for(int j = 0;j<size;j++){
                if(!set[j] //el nodo no esta en set 
					&&
					getEdge(nodes[u]->getData(),nodes[j]->getData()) // existe un edge entre u y j
					&&
					dist[u] != std::numeric_limits<int>::max() //la distancia no es infinito
					&&
					dist[u] + (getEdge(nodes[u]->getData(),nodes[j]->getData()))->getData() < dist[j]) //la distancia es menor
				{
					dist[j] = dist[u] + (getEdge(nodes[u]->getData(),nodes[j]->getData()))->getData();
					parent[j] = u;
                }
            }
        }
		cout << "||||||||DIJKSTRA||||||||\n\n";
		cout << "Vertex\tDistance from src\tParent node\n";
		for (int i = 0; i < size; i++) {
			cout << nodes[i]->getData() << "\t\t";
			if (dist[i] == std::numeric_limits<int>::max()) {
				cout << "INF\t\t";
			}
			else {
				cout << dist[i] << "\t\t";
			}
			cout << nodes[parent[i]]->getData() << "\n";
		}

		for (auto ni : nodes) {
			newGraph->insertNode(ni->getData(), ni->getX(), ni->getY());
		}
		for (int i = 0; i < size; i++) {
			auto edge = getEdge(nodes[parent[i]]->getData(), nodes[i]->getData());
			if (edge != nullptr) {
				newGraph->insertEdge(nodes[parent[i]]->getData(), nodes[i]->getData(), edge->getData(), edge->getDir());
			}
		//getEdge(nodes[parent[i]]->getData(), nodes[i]->getData())->getData()
		//nodes[parent[i]]->getData()
		//nodes[i]->getData()
		}
		cout << "\n||||||||DIJKSTRA||||||||\n\n";
		return newGraph;
    }

    int minDist(int dist[], bool set[]){
        int size = nodes.size();
        int min = std::numeric_limits<int>::max();
        int min_index;
        for(int i = 0;i<size;i++){
            if(set[i]==false && dist[i]<=min){
                min = dist[i];
                min_index = i;
            }
        }
		return min_index;
    }
    void print(){
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



    Graph* A_star(N orig, N dest)
    {
        auto newGraph = new Graph;
        // printf("\nA* (A Star) Function\n");

        nodeA = new sNode[nodes.size()];
        uint8_t i = 0;

        for (auto ni : nodes)
        {
            newGraph->insertNode(ni->getData(), ni->getX(), ni->getY());
            ni->setReached(0);
            nodeA[i].content = ni;
            nodeA[i].fGlobalGoal = std::numeric_limits<int>::max();
            nodeA[i].fLocalGoal= std::numeric_limits<int>::max();
            nodeA[i].parent = nullptr;
            i++;
        }

        for(uint8_t j = 0; j <nodes.size(); j++)
        {
            for(auto ei : nodeA[j].content->getEdgeVector())
            {
                nodeA[j].vecNeighbours.push_back(&nodeA[ei->getDest()->getData()]);
            }
        }


        auto origNode = getNode(orig);
        auto destNode = getNode(dest);

        nodeStart = &nodeA[orig];
        nodeEnd = &nodeA[dest];

        sNode* current = nodeStart;

        current->fLocalGoal = 0.0f;
        current->fGlobalGoal = distance(origNode, destNode);

        list<sNode*> listNotTestedNodes;
        listNotTestedNodes.push_back(nodeStart);

        while(!listNotTestedNodes.empty() && current != nodeEnd)
        {
            listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs){
                return lhs->fGlobalGoal < rhs->fGlobalGoal;
            });

            while(!listNotTestedNodes.empty() && listNotTestedNodes.front()->content->getReached())
                listNotTestedNodes.pop_front();

            if (listNotTestedNodes.empty())
                break;

            current = listNotTestedNodes.front();
            current->content->setReached(true);


            for (auto nodeNeighbour : current->vecNeighbours)
            {
                if (!nodeNeighbour->content->getReached())
                    listNotTestedNodes.push_back(nodeNeighbour);

                float fPossiblyLowerGoal = current->fLocalGoal + getEdge(current->content->getData(), nodeNeighbour->content->getData())->getData();;

                if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
                {
                    nodeNeighbour->parent = current;
                    nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

                    nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + distance(nodeNeighbour->content, nodeEnd->content);

                }
            }


        }
        current = nodeEnd;
        while(current != nodeStart)
        {
            if(current->parent != nullptr)
            {
                auto temp_init = current->parent->content->getData();
                auto temp_end = current->content->getData();
                auto temp_edge = getEdge(temp_init, temp_end);
                newGraph->insertEdge(temp_init ,temp_end, temp_edge->getData(), temp_edge->getDir());
            }
            current = current->parent;
        }

        return newGraph;
    }

    double distance(node* a, node* b)
    {
        return sqrt((a->getX() - b->getX())*(a->getX() - b->getX()) + (a->getY() - b->getY())*(a->getY() - b->getY()));
    };

    
    Graph* BellmanFord(int src)
    {

        int V = this->nodes.size();
        int E = this->edgess.size();
        int dist[V];

        for (int i = 0; i < V; i++){
            dist[i] = std::numeric_limits<int>::max();
            parent[i] = i;
        }
        dist[src] = 0;

        for (int i = 1; i <= V-1; i++)
        {
            for(auto ei: edgess)
            {
                int nodeOrig = ei->getOrigin()->getData();
                int nodeDest = ei->getDest()->getData();
                int weight = ei->getData();
                if(dist[nodeOrig] != std::numeric_limits<int>::max() && dist[nodeOrig] + weight < dist[nodeDest])
                    dist[nodeDest] = dist[nodeOrig] + weight;
            }
        }

        for(auto ei: edgess)
        {
            int nodeOrig = ei->getOrigin()->getData();
            int nodeDest = ei->getDest()->getData();
            int weight = ei->getData();
            if(dist[nodeOrig] != std::numeric_limits<int>::max() && dist[nodeOrig] + weight < dist[nodeDest])
                printf("Graph contains negative weight cycle");
        }


        printf("\nNode\tDistance\n");
        for (int i = 0; i < V; ++i)
            printf("%2d \t\t %2d\n", i, dist[i]);

        for (auto ni : nodes) {
            newGraph->insertNode(ni->getData(), ni->getX(), ni->getY());
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
    bool direction;

    struct sNode
    {
        node* content;
        float fGlobalGoal;              // Distance to goal so far
        float fLocalGoal;               // Distance to goal if we took the alternative route
        vector<sNode*> vecNeighbours;   // Connections to neighbours
        sNode* parent;                  // Node connecting to this node that offers shortest parent
    };

    sNode *nodeA = nullptr;
    sNode *nodeStart = nullptr;
    sNode *nodeEnd = nullptr;
};

typedef Graph<Traits> graph;

#endif
