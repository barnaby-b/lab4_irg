#pragma once
#include<glm/glm.hpp>
#include <array>

class Light
{
	glm::vec3 pos_;
	std::array<double, 3> ambient_intensities_;
	std::array<double, 3> diffuse_intesities_;
	std::array<double, 3> specular_intensities_;

public:

	Light(glm::vec3 pos, std::array<double, 3> ambient_intensities,
	      std::array<double, 3> diffuse_intesities,
	      std::array<double, 3> specular_intensities);

	~Light() = default;


	const glm::vec3& pos() const;
	const std::array<double, 3>& ambient_intensities() const;
	const std::array<double, 3>& diffuse_intesities() const;
	const std::array<double, 3>& specular_intensities() const;
};

