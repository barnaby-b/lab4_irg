#include "Renderer.hpp"
#include <string>
#include <GL/glut.h>

const std::tuple<int, int> Renderer::default_dimensions = std::tuple<int, int>{ 800, 600 };
std::tuple<int, int> Renderer::dimensions_ = default_dimensions;

void Renderer::render()
{
	const auto limit = 30;
	glPointSize(1);
	glColor3f(0.0f, 0.7f, 0.3f);
	glBegin(GL_POINTS);

	for(auto brojac = 0; brojac < 200000; ++brojac)
	{
		auto x0 = 0.0;
		auto y0 = 0.0;

		for(auto iter = 0; iter < limit; ++iter)
		{
			double x, y;

			auto p = rand() % 100;
			if(p < 1)
			{
				x = 0;
				y = 0.16*y0;
			} else if(p < 8)
			{
				x = 0.2*x0 - 0.26*y0 + 0;
				y = 0.23*x0 + 0.22*y0 + 1.6;
			} else if(p < 15)
			{
				x = -0.15*x0 + 0.28*y0 + 0;
				y = 0.26*x0 + 0.24*y0 + 0.44;

			} else
			{
				x = 0.85*x0 + 0.04*y0 + 0;
				y = -0.04*x0 + 0.85*y0 + 1.6;
			}

			x0 = x;
			y0 = y;
		}

		glVertex2i(round(x0 * 80 + 300), round(y0 * 60));
	}
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