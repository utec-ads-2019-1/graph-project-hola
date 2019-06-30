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
	graph graph1;
		
	public:
		Read(string* txt) {
			string line;

			ifstream file(txt->c_str());

			if (!file) cout << "error\n";

			while(!file.eof()) {
				getline(file, line);
				cout << line;
			}
    }
		
		graph& getGraph() {
        }
};

#endif
