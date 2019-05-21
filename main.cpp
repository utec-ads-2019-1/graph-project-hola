//#include <GL/glut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {

    cout << "---------------" << endl;
    cout << "Graph test" << endl;
    cout << "---------------" << endl;


    graph graph1;

    graph1.insertNode('A');
    graph1.insertNode('B');
    graph1.insertNode('C');
    graph1.insertNode('D');

    graph1.insertEdge('A', 'C', 15);
    graph1.insertEdge('B', 'C', 7);
    graph1.insertEdge('A', 'B', 2);
    graph1.insertEdge('C', 'A', 3);

    graph1.insertEdge('A', 'B', 10);


    cout << "\nSize: " << graph1.size() << endl << endl;

    graph1.print();

    return EXIT_SUCCESS;
}
