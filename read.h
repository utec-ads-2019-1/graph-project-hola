#ifndef READ_H
#define READ_H

#include "graph.h"
#include <fstream>


using namespace std;
/**
 * Clase de ayuda para leer el grafo desde un archivo,
 * no es necesario que la utilicen, podrían implementar su lector
 * desde su grafo o algún otro lado
 **/
template <typename G>
class Read {
	typedef typename G::N N;
	typedef typename G::E E;
	typedef typename G::self graph;
	typedef typename G::R R;
	graph graph1;
		
	public:
		Read(string* txt) {
			string line;

			ifstream file(txt->c_str());

			if (!file) cout << "error\n";

			int num_nodes, num_edges, weight;
			bool directed;
			char node, edge_init, edge_end;
			
			file >> num_nodes >> directed;
			graph1.setDirected(directed);
			graph1.setSize(num_nodes);

			for (int i = 0; i < num_nodes; i++) {
				file >> node;
				graph1.insertNode(node);
			}

			file >> num_edges;

			for (int j = 0; j < num_edges; j++) {
				file >> edge_init >> edge_end >> weight;
				graph1.insertEdge(edge_init, edge_end, weight);
			}

    }
		
		graph& getGraph() {
			return graph1;
    }
};

#endif
