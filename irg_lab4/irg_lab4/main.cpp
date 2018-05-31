#include "GlobalRenderer.hpp"
#include "Mesh.hpp"
#include <iostream>
#include "Scene.h"

int main(int argc, char *argv[])
{
	const auto object_normalized = Mesh::from_stream(std::cin).normalize();
	Scene default_scene{ object_normalized, {3, 4, 1}, {0, 0, 0}, {0, 1, 0} };
	GlobalRenderer::instance().renderer.init(argc, argv, "Laboratorijska vjezba 4");
	return 0;
}
