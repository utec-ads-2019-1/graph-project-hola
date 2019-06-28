//#include <GL/glut.h>
#include <iostream>
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {

    cout << "---------------" << endl;
    cout << "Graph test" << endl;
    cout << "---------------" << endl;


    graph graph1;
/*
    graph1.insertNode('A');
    graph1.insertNode('B');
    graph1.insertNode('C');
    graph1.insertNode('D');
    graph1.insertNode('E');
    graph1.insertNode('F');
    graph1.insertNode('G');
    graph1.insertNode('H');



    graph1.insertEdge('A', 'B', 11);
    graph1.insertEdge('A', 'C', 24);
    graph1.insertEdge('A', 'F', 1);
    graph1.insertEdge('B', 'F', 4);
    graph1.insertEdge('B', 'D', 1);
    graph1.insertEdge('B', 'E', 30);
    graph1.insertEdge('B', 'H', 17);
    graph1.insertEdge('C', 'F', 3);
    graph1.insertEdge('C', 'D', 21);
    graph1.insertEdge('C', 'G', 11);
    graph1.insertEdge('D', 'G', 6);
    graph1.insertEdge('D', 'F', 9);
    graph1.insertEdge('D', 'E', 51);
    graph1.insertEdge('E', 'H', 2);
*/


    graph1.insertNode('A');
    graph1.insertNode('B');
    graph1.insertNode('C');
    graph1.insertNode('D');
    graph1.insertNode('E');
    graph1.insertNode('F');
    graph1.insertNode('G');
    graph1.insertNode('H');
    graph1.insertNode('I');


    graph1.insertEdge('A', 'B');
    graph1.insertEdge('A', 'D');
    graph1.insertEdge('A', 'E');
    graph1.insertEdge('A', 'C');
    graph1.insertEdge('B', 'D');
    graph1.insertEdge('B', 'C');
    graph1.insertEdge('D', 'C');
    graph1.insertEdge('C', 'E');
    graph1.insertEdge('C', 'F');
    graph1.insertEdge('E', 'H');
    graph1.insertEdge('E', 'G');
    graph1.insertEdge('H', 'I');

    std::cout<<"Es conexo: "<<graph1.connected()<<"\n";
    std::cout<<"Es bipartito: "<<graph1.bipartite()<<"\n";

    cout << "\nDensity: " << graph1.isDense() << endl << endl;

    graph1.print();
    graph1.print2();

    cout << "\n\nBFS: \n" ;
    auto bfs1 = graph1.BFS('A');
    bfs1->print();

    cout << "\n\nDFS: \n" ;
    auto dfs1 = graph1.DFS('A');
    dfs1->print();

    printf("\n\nStrongly Connected: %d", graph1.StronglyConnected());
/*
    std::cout<<"\n\nKRUSKAL"<<"\n";

    graph* kruskal = graph1.MST_Kruskal();
    
    kruskal->print();
    
    std::cout<<"\n\nPPRIM\n";
    graph* prim = graph1.MST_Prim();
    prim->print();
  */
    return EXIT_SUCCESS;
    
    // std::cout<<"\n\nKRUSKAL"<<"\n";

    // graph* kruskal = graph1.MST_Kruskal();
    
    // kruskal->print();
    
    // std::cout<<"\n\nPRIM\n";
    // graph* prim = graph1.MST_Prim();
    // prim->print();
}
