#include<iostream>

#include<GL/glut.h>

#include "GlobalRenderer.hpp"

int main(int argc, char *argv[])
{
	using namespace std;
	GlobalRenderer::instance().renderer.init(argc, argv, "Laboratorijska vjezba 4");
	return 0;
}