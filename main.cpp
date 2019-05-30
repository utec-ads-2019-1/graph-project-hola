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

    graph1.insertEdge('A', 'B', 5);
    graph1.insertEdge('B', 'C', 8);
    graph1.insertEdge('B', 'A', 5);
    graph1.insertEdge('C', 'D', 2);
    graph1.insertEdge('C', 'F', 20);
    graph1.insertEdge('C', 'B', 8);
    graph1.insertEdge('D', 'C', 2);
    graph1.insertEdge('D', 'F', 9);
    graph1.insertEdge('D', 'E', 3);
    graph1.insertEdge('E', 'D', 3);
    graph1.insertEdge('E', 'G', 10);
    graph1.insertEdge('F', 'C', 20);
    graph1.insertEdge('F', 'D', 9);
    graph1.insertEdge('F', 'G', 50);
    graph1.insertEdge('G', 'F', 50);
    graph1.insertEdge('G', 'E', 10);


    std::cout<<"Es conexo: "<<graph1.connected()<<"\n";
    
    cout << "\nDensity: " << graph1.density() << endl << endl;

    graph1.print();

    std::cout<<"KRUSKAL"<<"\n\n";

    graph* kruskal = graph1.MST_Kruskal();
    
    kruskal->print();

    // auto prim = graph1.MST_Prim();
    // prim->print();
    
 /*   cout << "\n\nBFS: \n" ;
    auto bfs1 = graph1.BFS('B');
    bfs1->print();

    cout << "\n\nDFS: \n" ;
    auto dfs1 = graph1.DFS('B');
    dfs1->print();
*/
    return EXIT_SUCCESS;
}
