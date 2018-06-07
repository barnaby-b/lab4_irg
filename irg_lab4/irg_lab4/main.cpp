#include "GlobalRenderer.hpp"
#include "Mesh.hpp"
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "IFSDescriptor.h"
#include <random>
#include <map>

int main(int argc, char *argv[])
{

	std::ifstream ifs_file("ifs_def.txt");
	const auto ifs = IfsDescriptor::from_stream(ifs_file);

	const auto object_normalized = Mesh::from_stream(std::cin).normalize();
	const auto renderer = GlobalRenderer::instance().renderer;
	Renderer::set_ifs(ifs);
	renderer.init(argc, argv, "Laboratorijska vjezba 4");
	glutMainLoop();
	return 0;
}
