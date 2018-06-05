#pragma once

#include <tuple>
#include <string>
#include "Scene.h"
#include "Light.h"
#include "Material.h"

class Renderer
{
	static const std::tuple<int, int> default_dimensions;
	static Scene scene_;
	static Light light_;
	static Material material_;

public:
	Renderer() = default;

	void init(int& argc, char* argv[], const std::string& window_title) const;
	static void initialize_lighting();
	static void display();
	static void reshape(int width, int height);
	static void key_up(unsigned char key, int x, int y);


	static const Scene& get_scene();

	static void set_scene(const Scene& s);
	static void render();
};

