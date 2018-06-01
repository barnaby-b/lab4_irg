#pragma once

#include <tuple>
#include <string>
#include "Scene.h"

class Renderer
{
	static const std::tuple<int, int> default_dimensions;
	static Scene scene_;
	static int iter_;

public:
	Renderer() = default;

	void init(int& argc, char* argv[], const std::string& window_title) const;
	static void display();
	static void reshape(int width, int height);


	static const Scene& get_scene();

	static void set_scene(const Scene& s);
	static void render();
};

