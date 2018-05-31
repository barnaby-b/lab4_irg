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
	float z_far;
	
public:

	Scene(Mesh object, const glm::vec3 eye, const glm::vec3 center, const glm::vec3 up, float z_near = 0.0f, float z_far = 100.0f)
		: object_(std::move(object)),
		  eye_(eye),
		  center_(center),
		  up_(up),
		  z_near_(z_near),
		  z_far(z_far)
	{
	}
};

