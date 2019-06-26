#ifndef READ_H
#define READ_H

#include "graph.h"
#include <fstream>
#include <iostream>
/**
 * Clase de ayuda para leer el grafo desde un archivo,
 * no es necesario que la utilicen, podrían implementar su lector
 * desde su grafo o algún otro lado
 **/
template <typename G>
class Read {
	typedef typename G::N N;
	typedef typename G::E E;
		
	public:
		std::ifstream f;
		graph graph1;
		Read(char* file) {
			int Nodes;
			int Edges;
			N a;
			N b;
			E w;
			double x;
			double y;
			bool d;
			f.open(file);
			if(!f){
				std::cout<<"Error al leer el file :c\n";
			}
			f>>Nodes;
			for(int i =0;i<Nodes;i++){
				f>>a>>x>>y;
				graph1.insertNode(a,x,y);
			}
			f>>Edges;
			for(int i =0;i<Edges;i++){
				f>>a>>b>>w>>d;
				graph1.insertEdge(a,b,w,d);
			}

        }
		
		graph& getGraph() {
        }
};

#endif