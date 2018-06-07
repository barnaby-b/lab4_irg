#include "GlobalRenderer.hpp"
#include "Mesh.hpp"
#include <iostream>
#include <GL/glut.h>

int main(int argc, char *argv[])
{
	const auto object_normalized = Mesh::from_stream(std::cin).normalize();
	const auto renderer = GlobalRenderer::instance().renderer;
	renderer.init(argc, argv, "Laboratorijska vjezba 4");
	glutMainLoop();
	return 0;
}
