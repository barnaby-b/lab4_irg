#include<iostream>

#include<GL/glut.h>

#include "GlobalRenderer.hpp"

void reshape(int width, int height);
void display();


void display()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//draw code
	glPointSize(1.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	glVertex2i(0, 0);
	glVertex2i(2, 2);
	glVertex2i(4, 4);
	glEnd();

	glutSwapBuffers();
}

void reshape(const int width, const int height)
{
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width - 1, height - 1, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char *argv[])
{
	using namespace std;
	auto a = GlobalRenderer::instance();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(200, 200);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Primjer 1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	
	return 0;
}