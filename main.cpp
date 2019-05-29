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
    graph1.insertNode('E');
    graph1.insertNode('F');
    graph1.insertNode('G');
    graph1.createDS();

    graph1.insertEdge('A', 'G', 13);
    graph1.insertEdge('A', 'D', 8);
    graph1.insertEdge('B', 'E', 52);
    graph1.insertEdge('B', 'C', 17);
    graph1.insertEdge('B', 'D', 83);
    graph1.insertEdge('B', 'F', 97);
    graph1.insertEdge('B', 'G', 60);
    graph1.insertEdge('C', 'A', 4);
    graph1.insertEdge('D', 'B', 97);
    graph1.insertEdge('D', 'C', 37);
    graph1.insertEdge('D', 'F', 22);
    graph1.insertEdge('D', 'E', 41);
    graph1.insertEdge('E', 'A', 45);
    graph1.insertEdge('E', 'F', 92);
    graph1.insertEdge('F', 'A', 12);
    graph1.insertEdge('F', 'B', 8);
    graph1.insertEdge('G', 'D', 17);
    
    cout << "\nDensity: " << graph1.density() << endl << endl;

    graph1.print();

    auto prim = graph1.MST_Prim();
    prim->print();
    
 /*   cout << "\n\nBFS: \n" ;
    auto bfs1 = graph1.BFS('B');
    bfs1->print();

    cout << "\n\nDFS: \n" ;
    auto dfs1 = graph1.DFS('B');
    dfs1->print();
*/
    return EXIT_SUCCESS;
}
