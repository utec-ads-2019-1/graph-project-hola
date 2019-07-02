//#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <glut.h>
#include <GLFW/glfw3.h>

#include "graph.h"
#include "read.h"

#define WINDOW 950

using namespace std;

int main(int argc, char *argv[]) {
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

    cout << "---------------" << endl;
    cout << "Graph test" << endl;
    cout << "---------------" << endl;

		string file = "input.txt";
		Read<graph> read1(&file);
		graph graph1 = read1.getGraph();
		graph1.print();
		graph1.Floyd_Warshall();
			
		glfwSwapBuffers(window);				//Swap de los buffers
		glfwPollEvents();
		}
		
		glfwTerminate();

    return EXIT_SUCCESS;
    
}
