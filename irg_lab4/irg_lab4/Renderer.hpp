#pragma once

#include <tuple>
#include <string>
#include "Scene.h"

class Renderer
{
	static const std::tuple<int, int> default_dimensions;
	Scene scene_{Scene::empty_scene()};

public:
	Renderer() = default;

	void init(int& argc, char* argv[], const std::string& window_title) const;
	static void display();
	static void reshape(const int width, const int height);


	const Scene& scene() const;

	void set_scene(const Scene& scene);
};

