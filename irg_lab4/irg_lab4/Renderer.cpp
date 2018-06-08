#include "Renderer.hpp"
#include <string>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <random>
#include "parser_helper.hpp"

const std::tuple<int, int> Renderer::default_dimensions = std::tuple<int, int>{ 800, 600 };
std::tuple<int, int> Renderer::dimensions_ = default_dimensions;
IfsDescriptor Renderer::ifs_{ 0, 0, {}, {{}} };

void Renderer::render()
{
	glPointSize(1);
	glColor3f(0.0f, 0.7f, 0.3f);
	

	auto weights = ifs_.weights();
	if(weights.empty())
	{
		return;
	}

	auto table = ifs_.table();
	const auto ifs_points = ifs_.points_number();
	const auto ifs_limit = ifs_.limit();

	std::vector<int> weights_scaled;
	weights_scaled.reserve(weights.size());
	for(auto w : weights)
	{
		weights_scaled.push_back(static_cast<int>(w * 100));
	}

	std::vector<int> possible_indices;
	possible_indices.reserve(weights.size());
	for(auto i = 0u; i < weights.size(); i++)
	{
		possible_indices.push_back(i);
	}

	for(auto brojac = 0; brojac < ifs_points; ++brojac)
	{
		auto x0 = 0.0;
		auto y0 = 0.0;

		for(auto iter = 0; iter < ifs_limit; ++iter)
		{
			const auto ind = my_rand(possible_indices, weights_scaled, weights_scaled.size());
			const auto chosen_transform = table[ind];
			x0 = chosen_transform[0] * x0 + chosen_transform[1] * y0 + chosen_transform[4];;
			y0 = chosen_transform[2] * x0 + chosen_transform[3] * y0 + chosen_transform[5];;
		}


		glBegin(GL_POINTS);
		glVertex2i(static_cast<int>(round(x0 * std::get<0>(ifs_.etas()) + std::get<1>(ifs_.etas()))), 
			       static_cast<int>(round(y0 *  std::get<2>(ifs_.etas()) + std::get<3>(ifs_.etas()))));
		glEnd();
		if (brojac % 1000 == 0) {
			std::cout << brojac << std::endl;
		}
	}
}

void Renderer::set_ifs(const IfsDescriptor& ifs)
{
	ifs_ = ifs;

}

void Renderer::init(int & argc, char * argv[], const std::string & window_title) const
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(std::get<0>(default_dimensions), std::get<1>(default_dimensions));
	glutInitWindowPosition(0, 0);
	glutCreateWindow(window_title.c_str());
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
}

void Renderer::display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//render scene
	render();

	glFlush();
	glutSwapBuffers();
}

void Renderer::reshape(const int width, const int height)
{
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width - 1, 0, height - 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	dimensions_ = { width, height };
}