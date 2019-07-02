//#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <glut.h>
#include <GLFW/glfw3.h>
#include "graph.h"
//#include "read.h"
#define WINDOW 950
using namespace std;

int main(int argc, char *argv[]) {

    cout << "---------------" << endl;
    cout << "Graph test" << endl;
    cout << "---------------" << endl;

		GLFWwindow* window;

		if (!glfwInit())				//Inicializa la libreria
			return -1;

		window = glfwCreateWindow(WINDOW, WINDOW, "hola", NULL, NULL);				//Crea la ventana
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);				//Crea el contexto

		graph graph1(5);
		graph1.insertNode('A', 9, 2);
		graph1.insertNode('B', 14, 7);
		graph1.insertNode('C', 10, 3);
		graph1.insertNode('D', 1, 5);
		graph1.insertNode('E', 0, 6);
		/*	graph1.insertNode('C',7,2);
			graph1.insertNode('D',3,4);
			graph1.insertNode('E',1,2);
			graph1.insertNode('F',2,5);
			graph1.insertNode('G',1,4);
			graph1.insertNode('H',4,1); */

		graph1.insertEdge('A', 'B', 12, 0);
		graph1.insertEdge('B', 'D', 7, 0);
		graph1.insertEdge('B', 'E', 3, 0);
		graph1.insertEdge('E', 'A', 9, 0);
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
		graph dijkstra(5); 
		dijkstra = *(graph1.Dijkstra('B'));

		while (!glfwWindowShouldClose(window))				//Loop hasta que se cierra la ventana
		{
			glClear(GL_COLOR_BUFFER_BIT);

			//graph1.drawGraph();
			dijkstra.drawGraph();

 glfwSwapBuffers(window);				//Swap de los buffers
 glfwPollEvents();
}
		glfwTerminate();
    return EXIT_SUCCESS;
    
}
