#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <istream>

class Mesh
{
	std::vector<glm::vec3> vtxs_;
	std::vector<std::array<int, 3>> faces_;
	std::vector<glm::vec4> planes_;

	void compute_planes();
	

public:
	Mesh(std::vector<glm::vec3> vtxs, std::vector<std::array<int, 3>> faces);
	~Mesh();

	void normalize();

	std::string as_obj();
	static Mesh from_stream(std::istream& is);



	//Operators
	Mesh(const Mesh& other) = default;

	Mesh(Mesh&& other) noexcept
		: vtxs_(std::move(other.vtxs_)),
		  faces_(std::move(other.faces_)),
		  planes_(std::move(other.planes_))
	{
	}

	Mesh& operator=(const Mesh& other)
	{
		if (this == &other)
			return *this;
		vtxs_ = other.vtxs_;
		faces_ = other.faces_;
		planes_ = other.planes_;
		return *this;
	}

	Mesh& operator=(Mesh&& other) noexcept
	{
		if (this == &other)
			return *this;
		vtxs_ = std::move(other.vtxs_);
		faces_ = std::move(other.faces_);
		planes_ = std::move(other.planes_);
		return *this;
	}
};


