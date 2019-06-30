//#include <GL/glut.h>
#include <iostream>
#include "graph.h"
#include "read.h"

using namespace std;

int main(int argc, char *argv[]) {

    cout << "---------------" << endl;
    cout << "Graph test" << endl;
    cout << "---------------" << endl;


    graph graph1(4)

graph1.insertNode('A');
graph1.insertNode('B');
graph1.insertNode('C');
graph1.insertNode('D');



graph1.insertEdge('A', 'B', 5, 1);
graph1.insertEdge('A', 'C', 9, 1);
graph1.insertEdge('B', 'C', 1, 1);
graph1.insertEdge('C', 'D', 2, 1);
graph1.insertEdge('D', 'B', 3, 1);
    
 /*   std::cout<<"Es conexo: "<<graph1.connected()<<"\n";
 
    std::cout<<"Es bipartito: "<<graph1.bipartite()<<"\n";

    cout << "\nDensity: " << graph1.density() << endl << endl;
*/
    graph1.print();
		graph1.Floyd_Warshall();
    
/*    cout << "\n\nBFS: \n" ;
    auto bfs1 = graph1.BFS('B');
    bfs1->print();

    cout << "\n\nDFS: \n" ;
    auto dfs1 = graph1.DFS('B');
    dfs1->print();

    bool a = graph1.StronglyConnected();
    cout << a;
    
    std::cout<<"\n\nKRUSKAL"<<"\n";

    graph* kruskal = graph1.MST_Kruskal();
    
    kruskal->print();
    
    std::cout<<"\n\nPPRIM\n";
    graph* prim = graph1.MST_Prim();
    prim->print();
   
    return EXIT_SUCCESS;
    
    // std::cout<<"\n\nKRUSKAL"<<"\n";

    // graph* kruskal = graph1.MST_Kruskal();
    
    // kruskal->print();
    
    // std::cout<<"\n\nPRIM\n";
    // graph* prim = graph1.MST_Prim();
    // prim->print();
*/
}
