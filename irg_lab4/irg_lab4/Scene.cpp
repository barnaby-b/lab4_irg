#include "Scene.h"

Scene::Scene(Mesh object, 
	const glm::vec3 eye, const glm::vec3 center, const glm::vec3 up, 
	const float z_near, const float z_far)
	: object_(std::move(object)),
	eye_(eye),
	center_(center),
	up_(up),
	z_near_(z_near),
	z_far(z_far)
{
}

const Mesh& Scene::object() const
{
	return object_;
}

const glm::vec3& Scene::eye() const
{
	return eye_;
}

const glm::vec3& Scene::center() const
{
	return center_;
}

const glm::vec3& Scene::up() const
{
	return up_;
}

float Scene::z_near() const
{
	return z_near_;
}

float Scene::z_far() const
{
	return z_far_;
}
