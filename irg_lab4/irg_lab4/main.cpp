#include "GlobalRenderer.hpp"
#include "Mesh.hpp"
#include <iostream>
#include "Scene.h"
#include <GL/glut.h>

int main(int argc, char *argv[])
{
	const auto object_normalized = Mesh::from_stream(std::cin).normalize();
	const auto renderer = GlobalRenderer::instance().renderer;
	renderer.init(argc, argv, "Laboratorijska vjezba 4 - rucno sjencanje");
	Renderer::set_scene({ object_normalized,{ 3, 4, 1 },{ 0, 0, 0 },{ 0, 1, 0 } });
	glutMainLoop();
	return 0;
}
