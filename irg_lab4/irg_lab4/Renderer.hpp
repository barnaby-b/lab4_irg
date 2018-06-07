#pragma once

#include <tuple>
#include <string>
#include "Scene.h"
#include <stack>

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
	static bool use_cube_fn_;

	static std::stack<plane_params> complex_params_stack_;


public:
	Renderer() = default;

	void init(int& argc, char* argv[], const std::string& window_title) const;
	static complex screen_to_complex(int x, int y);
	static void display();
	static void reshape(int width, int height);
	static void key_up(unsigned char key, int x, int y);
	static void mouse_func(int button, int state, int x, int y);
	static void render();
	static void set_gl_color_frac(int n);
	static void increase_zoom(int x, int y);
	static void decrease_zoom();
};

