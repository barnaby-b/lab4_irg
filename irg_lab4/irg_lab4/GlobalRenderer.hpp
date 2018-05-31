#pragma once
#include "Renderer.hpp"
#include <memory>

class GlobalRenderer
{
	GlobalRenderer() = default;
	Renderer renderer_;

public:
	static GlobalRenderer & instance();
};

