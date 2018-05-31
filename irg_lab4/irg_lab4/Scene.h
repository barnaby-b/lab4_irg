#pragma once
#include "Mesh.hpp"
#include <glm/glm.hpp>

class Scene
{
	Mesh object_;
	glm::vec3 eye_;
	glm::vec3 center_;
	glm::vec3 up_;
	float z_near_;
	float z_far_;
	
public:

	Scene(Mesh object, 
		glm::vec3 eye, glm::vec3 center, glm::vec3 up, 
		float z_near = 0.0f, float z_far = 100.0f);

	static Scene empty_scene();

	const Mesh& object() const;
	const glm::vec3& eye() const;
	const glm::vec3& center() const;
	const glm::vec3& up() const;
	float z_near() const;
	float z_far() const;
};

