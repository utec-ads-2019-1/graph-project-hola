#ifndef DRAW_H
#define DRAW_H

#include <stdlib.h>
#include <GL/glew.h>
#include <glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#define WINDOW 950
#define REAL_RADIUS 1
#define RADIUS REAL_RADIUS * 0.05
#define NORM 0.05

void drawArrow(double x1, double y1, double x2, double y2) {
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(4.0);

	//Normalizar
	x1 *= NORM;
	y1 *= NORM;
	x2 *= NORM;
	y2 *= NORM;

	glBegin(GL_LINES);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	double vx = x1 - x2;						//variacion
	double vy = y1 - y2;						//variacion
	double m = vy / vx;							//Slope
	double d = sqrt(vx*vx + vy * vy);			//Modulo
	double s = 1.0f / d;					    //Vector unitario
	double r = (d - RADIUS) / d;				//Ratio
	double newX = ((1 - r)*x1 + r * x2);
	double newY = ((1 - r)*y1 + r * y2);
	vx *= s;
	vy *= s;

	//normalizar
	vx *= NORM;
	vy *= NORM;

	double angle = atan(m) * 180 / M_PI;
	double size = 0.5;
	double newx = x2;
	double newy = y2;

	glBegin(GL_LINES);
	glColor4f(0.0, 1.0, 0.0, 1.0);
	glVertex2f(newX, newY);
	glVertex2f(newX + size * (vx + vy), newY + size * (vy - vx));
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(newX, newY);
	glVertex2f(newX + size * (vx - vy), newY + size * (vy + vx));
	glEnd();
}
void drawLine(int weight, double x1, double y1, double x2, double y2) {
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.0);
	x1 *= 0.12;
	y1 *= 0.12;
	x2 *= 0.12;
	y2 *= 0.12;
	glBegin(GL_LINES);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
void drawCircle(char C, double x, double y) {
	double y0 = y - RADIUS / 2;
	double x0 = x - RADIUS / 2;
	x0 *= NORM;
	y0 *= NORM;
	x *= NORM;
	y *= NORM;
	int i;
	float triangleAmount = 1000.0f;
	float twicePi = 2.0f * M_PI;
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	for (i = 0; i <= triangleAmount; i++)
	{
		glVertex2f(x, y);
		float norm_x = x + (RADIUS * cos(i * twicePi / triangleAmount));
		float norm_y = y + (RADIUS * sin(i * twicePi / triangleAmount));

		glVertex2f(norm_x, norm_y);
	}
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
	glRasterPos2f(x0, y0);
	glutBitmapCharacter(font_style, C);

#endif