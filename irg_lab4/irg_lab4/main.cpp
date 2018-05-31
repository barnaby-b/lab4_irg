#include "GlobalRenderer.hpp"
#include "Mesh.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	auto cube = Mesh::from_stream(std::cin);
	std::cout << cube.as_obj() << std::endl;
	std::cout << "Norm: \n" << cube.normalize().as_obj() << std::endl;
	GlobalRenderer::instance().renderer.init(argc, argv, "Laboratorijska vjezba 4");
	return 0;
}
