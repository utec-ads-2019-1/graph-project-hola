//#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <glut.h>
#include <GLFW/glfw3.h>
#include "graph2.h"
#include "read.h"
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

	while (!glfwWindowShouldClose(window))				//Loop hasta que se cierra la ventana
	{
		glClear(GL_COLOR_BUFFER_BIT);

		graph graph1;

		graph1.insertNode('A',9,2);
		graph1.insertNode('B',14,7);
	/*	graph1.insertNode('C',7,2);
		graph1.insertNode('D',3,4);
		graph1.insertNode('E',1,2);
		graph1.insertNode('F',2,5);
		graph1.insertNode('G',1,4);
		graph1.insertNode('H',4,1); */

		graph1.insertEdge('A', 'B', 11);
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


	 	glfwSwapBuffers(window);				//Swap de los buffers
		glfwPollEvents();
	}

	glfwTerminate();



	// A star function
	graph graph2;
    
    graph2.insertNode(0, 13.0, 6.0);
    graph2.insertNode(1, 22.0, 6.0);
    graph2.insertNode(2, 18.0, 2.0);
    graph2.insertNode(3, 18.0, 13.3);
    graph2.insertNode(4, 22.0, 21.3);
    graph2.insertNode(5, 28.0, 14.3);
    graph2.insertNode(6, 38.4, 33.5);
    graph2.insertNode(7, 35.0, 18.3);
    graph2.insertNode(8, 46.2, 14.3);
    graph2.insertNode(9, 32.0, 3.7);
    graph2.insertNode(10, 40.3, 2.5);

    graph2.insertEdge(0 ,2 ,3 , 0);
    graph2.insertEdge(1 ,3 ,4 , 0);
    graph2.insertEdge(2 ,3 ,5 , 0);
    graph2.insertEdge(3 ,0 ,2 , 0);
    graph2.insertEdge(4 ,3 ,9 , 0);
    graph2.insertEdge(5 ,1 ,3 , 0);
    graph2.insertEdge(0 ,5 ,4 , 0);
    graph2.insertEdge(2 ,4 ,3 , 0);
    graph2.insertEdge(3 ,5 ,4 , 0);
    graph2.insertEdge(6 ,4 ,8 , 0);
    graph2.insertEdge(6 ,3 ,3 , 0);
    graph2.insertEdge(7 ,6 ,4 , 0);
    graph2.insertEdge(8 ,9 ,7 , 0);
    graph2.insertEdge(9 ,1 ,6 , 0);
    graph2.insertEdge(5 ,8 ,2 , 0);
    graph2.insertEdge(7 ,4 ,8 , 0);
    graph2.insertEdge(8 ,7 ,3 , 0);
    graph2.insertEdge(8 ,6 ,1 , 0);
    graph2.insertEdge(10 ,5 ,7 , 0);
    graph2.insertEdge(9 ,10 ,2 , 0);
    graph2.insertEdge(10 ,8 ,1 , 0);
    graph2.insertEdge(10 ,7 ,4 , 0);
    graph2.insertEdge(2 ,10 ,9 , 0);

	auto star = graph2.A_star(0, 4);

	graph1.BellmanFord(2);



    return EXIT_SUCCESS;
    
}
