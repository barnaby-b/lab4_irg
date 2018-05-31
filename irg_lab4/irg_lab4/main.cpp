#include "GlobalRenderer.hpp"

int main(int argc, char *argv[])
{
	GlobalRenderer::instance().renderer.init(argc, argv, "Laboratorijska vjezba 4");
	return 0;
}