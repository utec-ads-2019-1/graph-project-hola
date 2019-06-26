//#include <GL/glut.h>
#include <iostream>
#include "graph.h"
#include "read.h"
using namespace std;

int main(int argc, char *argv[]) {

    cout << "---------------" << endl;
    cout << "Graph test" << endl;
    cout << "---------------" << endl;


Read<G>::Read("./test.txt");

//     graph graph1;

// graph1.insertNode('A');
// graph1.insertNode('B');
// graph1.insertNode('C');
// graph1.insertNode('D');
// graph1.insertNode('E');
// graph1.insertNode('F');
// graph1.insertNode('G');
// graph1.insertNode('H');



// graph1.insertEdge('A', 'B', 11);
// graph1.insertEdge('A', 'C', 24);
// graph1.insertEdge('A', 'F', 1);
// graph1.insertEdge('B', 'F', 4);
// graph1.insertEdge('B', 'D', 1);
// graph1.insertEdge('B', 'E', 30);
// graph1.insertEdge('B', 'H', 17);
// graph1.insertEdge('C', 'F', 3);
// graph1.insertEdge('C', 'D', 21);
// graph1.insertEdge('C', 'G', 11);
// graph1.insertEdge('D', 'G', 6);
// graph1.insertEdge('D', 'F', 9);
// graph1.insertEdge('D', 'E', 51);
// graph1.insertEdge('E', 'H', 2);
    
//     std::cout<<"Es conexo: "<<graph1.connected()<<"\n";
//     std::cout<<"Es bipartito: "<<graph1.bipartite()<<"\n";

//     cout << "\nDensity: " << graph1.density() << endl << endl;

//     graph1.print();
    
//     cout << "\n\nBFS: \n" ;
//     auto bfs1 = graph1.BFS('B');
//     bfs1->print();

//     cout << "\n\nDFS: \n" ;
//     auto dfs1 = graph1.DFS('B');
//     dfs1->print();

//     bool a = graph1.StronglyConnected();
//     cout << a;
    
//     std::cout<<"\n\nKRUSKAL"<<"\n";

//     graph* kruskal = graph1.MST_Kruskal();
    
//     kruskal->print();
    
//     std::cout<<"\n\nPPRIM\n";
//     graph* prim = graph1.MST_Prim();
//     prim->print();
   
    return EXIT_SUCCESS;
    
    // std::cout<<"\n\nKRUSKAL"<<"\n";

    // graph* kruskal = graph1.MST_Kruskal();
    
    // kruskal->print();
    
    // std::cout<<"\n\nPRIM\n";
    // graph* prim = graph1.MST_Prim();
    // prim->print();
}
