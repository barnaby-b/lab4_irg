#include "Renderer.hpp"
#include <string>
#include <GL/glut.h>


int divergence_test(const complex c, const int limit)
{
	complex z;
	z.re = 0;
	z.im = 0;

	for (auto i = 0; i <= limit; ++i)
	{
		const auto next_re = z.re*z.re - z.im * z.im + c.re;
		const auto next_im = 2 * z.re*z.im + c.im;

		z.re = next_re;
		z.im = next_im;

		const auto mod_sq = z.re*z.re + z.im*z.im;
		if (mod_sq > 4)
		{
			return i;
		}
	}

	return -1;
}

const std::tuple<int, int> Renderer::default_dimensions = std::tuple<int, int>{ 800, 600 };
std::tuple<int, int> Renderer::dimensions_ = default_dimensions;

void Renderer::render()
{
	glColor3f(1, 0, 0);

	glBegin(GL_POINTS);
	for(auto x = 0; x < std::get<0>(dimensions_); ++x)
	{
		for(auto y = 0; y < std::get<1>(dimensions_); ++y)
		{
			const auto n = divergence_test(screen_to_complex(x, y), 128);
			set_gl_color_frac(n);
			glVertex2i(x, y);
		}
	}
	glEnd();
}

void Renderer::set_gl_color_frac(int n)
{
	if(n == -1)
	{
		glColor3f(0, 0, 0);
		return;
	}

	const auto limit = 128;
	const auto r = (n - 1) * 255.0f / limit;
	const auto g = ((n - 1) % (limit / 4)) * 255.0f / (limit / 4);
	const auto b = ((n - 1) % (limit / 8)) * 255.0f / (limit / 8);
	glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
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

complex Renderer::screen_to_complex(const int x, const int y)
{
	static auto xmin = 0;
	static auto xmax = 0;
	xmax = std::get<0>(dimensions_);
	

	static auto ymin = 0;
	static auto ymax = 0;
	ymax = std::get<1>(dimensions_);

	static auto umin = -2.0;
	static auto umax = 1.0;

	static auto vmin = -1.2;
	static auto vmax = 1.2;

	return
	{
		(x - xmin) / static_cast<double>(xmax - xmin) * (umax - umin) + umin,
		(y - ymin) / static_cast<double>(ymax - ymin) * (vmax - vmin) + vmin
	};
}

void Renderer::display()
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
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