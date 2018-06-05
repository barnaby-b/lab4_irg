#include "Renderer.hpp"
#include <string>
#include <GL/glut.h>


const std::tuple<int, int> Renderer::default_dimensions = std::tuple<int, int>{ 800, 600 };
Scene Renderer::scene_{};
Light Renderer::light_{ { -4, 5, 3 }, { 0.2f, 0.2f, 0.2f },{ 0.8f, 0.0f, 0 },{ 0.8f, 0.0f, 0 } };
Material Renderer::material_{{1.0f,1.0f,1},{1, 1.0f, 1},{0.01f, 0.01f, 0.01f}};

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
	
	auto i = 0u;
	for(auto face : scene_.object().faces())
	{
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
		auto vtx_coords = scene_.object().get_vertices_for_face(face);
		const auto center = (vtx_coords[0] + vtx_coords[1] + vtx_coords[2]) * 1.0f/3.0f;
		const auto light_vector = light_.pos() - center;
		const auto eye_vector = scene_.eye() - center;
		const auto normal = normalize(glm::vec3{ scene_.object().planes()[i][0],scene_.object().planes()[i][1], scene_.object().planes()[i][2] });
		const auto ref = reflect(light_vector, normal);

		std::array<float, 3> specular_emission{0, 0, 0};
		std::array<float, 3> diffuse_emission{ 0, 0, 0 };
		std::array<float, 3> ambient_emission{ 0, 0, 0 };

		for (auto ii = 0u; ii < 3; ++ii)
		{
			specular_emission[ii] = light_.specular_intensities()[ii] * material_.specular_emission()[ii] * dot(normalize(ref), normalize(eye_vector));
			diffuse_emission[ii] = std::max(light_.diffuse_intesities()[ii] * material_.diffuse_emission()[ii] * dot(normalize(light_vector), normalize(normal)), 0.0f);
			ambient_emission[ii]= light_.ambient_intensities()[ii] * material_.ambient_emission()[ii];
		}

		glColor3f(specular_emission[0] + diffuse_emission[0] + ambient_emission[0],
			specular_emission[1] + diffuse_emission[1] + ambient_emission[1],
			specular_emission[2] + diffuse_emission[2] + ambient_emission[2]);

		glVertex3f(vtx_coords[0][0], vtx_coords[0][1], vtx_coords[0][2]);
		glVertex3f(vtx_coords[1][0], vtx_coords[1][1], vtx_coords[1][2]);
		glVertex3f(vtx_coords[2][0], vtx_coords[2][1], vtx_coords[2][2]);
		glEnd();

		++i;
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
	float light_pos[]{ -4, 5, 3, 1 };
	float light_amb[]{ 0.2f, 0.2f, 0.2f, 1 };
	float light_dif[]{ 0.8f, 0.0f, 0, 1};
	float light_spc[]{ 0.8f, 0.0f, 0, 1};
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

