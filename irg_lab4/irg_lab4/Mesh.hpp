#pragma once
#include<vector>
#include<array>
#include<sstream>
#include<glm/glm.hpp>

class Mesh
{
	std::vector<glm::vec3> vtxs_;
	std::vector<std::array<int, 3>> faces_;
	std::vector<glm::vec4> planes_;

	void compute_planes();
	

public:
	Mesh(std::vector<glm::vec3> vtxs, std::vector<std::array<int, 3>> faces);
	~Mesh() = default;

	Mesh normalize();

	std::string as_obj();
	static Mesh from_stream(std::istream& is);
	std::array<glm::vec3, 3> get_vertices_for_face(std::array<int, 3> face) const;

	//Operators
	Mesh(const Mesh& other) = default;
	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(const Mesh& other);
	Mesh& operator=(Mesh&& other) noexcept;

	//Getters
	const std::vector<glm::vec3>& vtxs() const;
	const std::vector<std::array<int, 3>>& faces() const;
	const std::vector<glm::vec4>& planes() const;
};


