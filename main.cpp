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

    graph1.insertEdge('A', 'B', 8);
    graph1.insertEdge('A', 'D', 9);
    graph1.insertEdge('B', 'E', 20);
    graph1.insertEdge('B', 'A', 8);
    //graph1.insertEdge('C', 'F', 4);
    graph1.insertEdge('D', 'A', 9);
    graph1.insertEdge('D', 'F', 5);
    graph1.insertEdge('D', 'E', 20);
    graph1.insertEdge('E', 'D', 20);
    graph1.insertEdge('E', 'B', 10);
    graph1.insertEdge('F', 'D', 5);
    //graph1.insertEdge('F', 'C', 4);

    // graph1.createDS();

    std::cout<<"Es conexo: "<<graph1.connected()<<"\n";
    
    cout << "\nDensity: " << graph1.density() << endl << endl;

    graph1.print();

    // std::cout<<"KRUSKAL"<<"\n\n";

    // graph* kruskal = graph1.MST_Kruskal();
    
    // kruskal->print();

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
