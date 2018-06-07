#pragma once

#include <tuple>
#include <string>
#include "Scene.h"

typedef struct
{
	double re;
	double im;
} complex;

typedef std::tuple<double, double, double, double> plane_params;

class Renderer
{
	static const std::tuple<int, int> default_dimensions;
	static std::tuple<int, int> dimensions_;

	//umin, umax, vmin, vmax
	static plane_params complex_plane_params_;

	//xmin, xmax, ymin, ymax
	static plane_params real_plane_params_;

	static bool color_view_;


public:
	Renderer() = default;

	void init(int& argc, char* argv[], const std::string& window_title) const;
	static complex screen_to_complex(int x, int y);
	static void display();
	static void reshape(int width, int height);
	static void key_up(unsigned char key, int x, int y);
	static void render();
	static void set_gl_color_frac(int n);
};

