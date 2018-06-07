#pragma once

#include <tuple>
#include <string>
#include "Scene.h"

typedef struct
{
	double re;
	double im;
} complex;

class Renderer
{
	static const std::tuple<int, int> default_dimensions;
	static std::tuple<int, int> dimensions_;

public:
	Renderer() = default;

	void init(int& argc, char* argv[], const std::string& window_title) const;
	static void display();
	static void reshape(int width, int height);
	static void render();
};

