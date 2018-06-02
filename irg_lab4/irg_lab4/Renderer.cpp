#include "Renderer.hpp"
#include <string>
#include <GL/glut.h>


const std::tuple<int, int> Renderer::default_dimensions = std::tuple<int, int>{ 800, 600 };
Scene Renderer::scene_{};

void Renderer::render()
{
	float mat_amb[] = { 1, 1, 1, 1 };
	float mat_dif[] = { 1, 1, 0.5, 1 };
	float mat_spc[] = { 0.01f, 1.0f, 0.1f, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spc);
	glMaterialf(GL_FRONT, GL_SHININESS, 96);

	auto vtx_normals = scene_.object().vtx_normals();
	for(auto face : scene_.object().faces())
	{
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
		auto vtx_coords = scene_.object().get_vertices_for_face(face);
		glNormal3f(vtx_normals[face[0]][0], vtx_normals[face[0]][1], vtx_normals[face[0]][2]);
		glVertex3f(vtx_coords[0][0], vtx_coords[0][1], vtx_coords[0][2]);

		glNormal3f(vtx_normals[face[1]][0], vtx_normals[face[1]][1], vtx_normals[face[1]][2]);
		glVertex3f(vtx_coords[1][0], vtx_coords[1][1], vtx_coords[1][2]);

		glNormal3f(vtx_normals[face[2]][0], vtx_normals[face[2]][1], vtx_normals[face[2]][2]);
		glVertex3f(vtx_coords[2][0], vtx_coords[2][1], vtx_coords[2][2]);
		glEnd();
	}
}

void Renderer::init(int & argc, char * argv[], const std::string & window_title) const
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(std::get<0>(default_dimensions), std::get<1>(default_dimensions));
	glutInitWindowPosition(0, 0);
	glutCreateWindow(window_title.c_str());
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardUpFunc(key_up);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	initialize_lighting();
}

void Renderer::initialize_lighting()
{
	glEnable(GL_LIGHTING);
	float ambient[] = { 0, 0, 0, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	float light_pos[]{ -4, 5, 3, 1 };
	float light_amb[]{ 0.2f, 0.2f, 0.2f, 1 };
	float light_dif[]{ 0.8f, 0.0f, 0, 1};
	float light_spc[]{ 0, 0, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc);
	glEnable(GL_LIGHT0);
}

void Renderer::display()
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void Renderer::key_up(const unsigned char key, int, int)
{
	switch(key)
	{
	case 'r':
		{
		scene_.rotate_eye(10);
		break;
		}
	case 'l':
		{
		scene_.rotate_eye(-10);
		break;
		}
	case 'k' :
		{
		glShadeModel(GL_FLAT);
		glutPostRedisplay();
		break;
		}
	case 'g' :
		{
		glShadeModel(GL_SMOOTH);
		glutPostRedisplay();
		break;
		}
	default:
		{
			
		}
	}
}

const Scene& Renderer::get_scene()
{
	return scene_;
}

void Renderer::set_scene(const Scene& s)
{
	scene_ = s;
}

