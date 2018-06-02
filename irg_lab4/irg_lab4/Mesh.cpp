#include "Mesh.hpp"


void Mesh::compute_planes()
{
	planes_.clear();

	for(auto face : faces_)
	{
		auto face_coords = get_vertices_for_face(face);

		auto normal = (face_coords[1] - face_coords[0]) * (face_coords[2] - face_coords[0]);
		auto plane_coefficient_d = -face_coords[0][0] * normal[0] - face_coords[0][1] * normal[1] - face_coords[0][2] * normal[2];

		planes_.emplace_back(normal[0], normal[1], normal[2], plane_coefficient_d);
	}
}

void Mesh::compute_vtx_normals()
{

}

Mesh::Mesh(std::vector<glm::vec3> vtxs, std::vector<std::array<int, 3>> faces) :
	vtxs_(std::move(vtxs)),
	faces_(std::move(faces))
{
	compute_planes();
}

Mesh Mesh::normalize()
{
	glm::vec3 mins(vtxs_[0][0], vtxs_[0][1], vtxs_[0][2]);
	glm::vec3 maxs(vtxs_[0][0], vtxs_[0][1], vtxs_[0][2]);
	// Find minimum and maximum x, y and z coordinates
	for(auto vtx : vtxs_)
	{
		for(auto axis = 0; axis < 3; ++axis)
		{
			if(vtx[axis] < mins[axis])
			{
				mins[axis] = vtx[axis];
			}

			if (vtx[axis] > maxs[axis])
			{
				maxs[axis] = vtx[axis];
			}

		}
	}

	//find center coordinates
	auto center((maxs - mins) / 2.0f);

	//find max range over coordinates
	auto max_range = maxs[0] - mins[0];
	for (auto i = 1; i < 3; ++i)
	{
		if ((maxs[i] - mins[i]) > max_range)
		{
			max_range = maxs[i] - mins[i];
		}
	}

	//update vertices
	for (auto& vtx : vtxs_) {
		for(auto i = 0; i < 3; i++)
		{
			vtx[i] = (vtx[i] - center[i]) * (2 / max_range);
		}
	}


	return *this;
}

std::string Mesh::as_obj()
{
	std::stringstream result;

	for(auto vtx : vtxs_)
	{
		result << "v " 
			<< vtx[0] << ' ' << vtx[1] << ' ' << vtx[2] << '\n';
	}

	for (auto face : faces_)
	{
		result << "f " 
			<< face[0] + 1 << ' ' << face[1] + 1 << ' ' << face[2] + 1 << '\n';
	}

	return result.str();
}

Mesh Mesh::from_stream(std::istream& is)
{
	using namespace std;

	vector<glm::vec3> vtxs;
	vector<std::array<int, 3>> faces;

	for (string line; getline(is, line);)
	{
		stringstream sstream(line);
		auto entity_type = '\0';

		sstream >> entity_type;

		switch (entity_type)
		{

		case 'v': {

			float x = 0, y = 0, z = 0;
			if (!(sstream >> x >> y >> z))
			{
				throw domain_error("vertex format invalid");
			}

			vtxs.emplace_back(x, y, z);
			break;
		}
		case 'f': {

			int v1_ind = 0, v2_ind = 0, v3_ind;

			if (!(sstream >> v1_ind >> v2_ind >> v3_ind))
			{
				throw domain_error("face format invalid");
			}

			faces.push_back({ v1_ind - 1, v2_ind - 1, v3_ind - 1 });

			break;
		}
		default: {
			break;
		}
		}
	}

	return Mesh(vtxs, faces);
}

std::array<glm::vec3, 3> Mesh::get_vertices_for_face(std::array<int, 3> face) const
{

	return { vtxs_[face[0]], vtxs_[face[1]], vtxs_[face[2]] };
}

Mesh::Mesh(Mesh&& other) noexcept: vtxs_(std::move(other.vtxs_)),
                                   faces_(std::move(other.faces_)),
                                   planes_(std::move(other.planes_))
{
}

Mesh& Mesh::operator=(const Mesh& other)
{
	if (this == &other)
		return *this;
	vtxs_ = other.vtxs_;
	faces_ = other.faces_;
	planes_ = other.planes_;
	return *this;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	if (this == &other)
		return *this;
	vtxs_ = std::move(other.vtxs_);
	faces_ = std::move(other.faces_);
	planes_ = std::move(other.planes_);
	return *this;
}

const std::vector<glm::vec3>& Mesh::vtxs() const
{
	return vtxs_;
}

const std::vector<std::array<int, 3>>& Mesh::faces() const
{
	return faces_;
}

const std::vector<glm::vec4>& Mesh::planes() const
{
	return planes_;
}
