#include "Renderer.hpp"
#include <string>
#include <GL/glut.h>


const std::tuple<int, int> Renderer::default_dimensions = std::tuple<int, int>{ 800, 600 };
Scene Renderer::scene_{};

void Renderer::render()
{
	glColor3f(1, 0, 0);
	for(auto face : scene_.object().faces())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		auto vtx_coords = scene_.object().get_vertices_for_face(face);
		glVertex3f(vtx_coords[0][0], vtx_coords[0][1], vtx_coords[0][2]);
		glVertex3f(vtx_coords[1][0], vtx_coords[1][1], vtx_coords[1][2]);
		glVertex3f(vtx_coords[2][0], vtx_coords[2][1], vtx_coords[2][2]);
		glEnd();
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

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::display()
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(scene_.eye()[0], scene_.eye()[1], scene_.eye()[2],
		scene_.center()[0], scene_.center()[1], scene_.center()[2],
		scene_.up()[0], scene_.up()[1], scene_.up()[2]);

	render();

	
	glFlush();
	glutSwapBuffers();
}

void Renderer::reshape(const int width, const int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glFrustum(- scene_.near_w() / 2, scene_.near_w() / 2,
		- scene_.near_h() / 2, scene_.near_h() / 2,
		scene_.z_near(), scene_.z_far());

	glMatrixMode(GL_MODELVIEW);
	
}

const Scene& Renderer::get_scene()
{
	return scene_;
}

void Renderer::set_scene(const Scene& s)
{
	scene_ = s;
}

