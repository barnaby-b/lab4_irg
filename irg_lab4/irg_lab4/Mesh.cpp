#include "Mesh.hpp"

#include<array>
#include<sstream>

#include<glm/vec3.hpp>


void Mesh::compute_planes()
{
	planes_.clear();

	for(auto face : faces_)
	{
		auto face_coords = std::array<glm::vec3, 3>{ vtxs_[face[0]], vtxs_[face[1]], vtxs_[face[2]] };

		auto normal = (face_coords[1] - face_coords[0]) * (face_coords[2] - face_coords[0]);
		auto plane_coefficient_d = -face_coords[0][0] * normal[0] - face_coords[0][1] * normal[1] - face_coords[0][2] * normal[2];

		planes_.emplace_back(normal[0], normal[1], normal[2], plane_coefficient_d);
	}
}

Mesh::Mesh(std::vector<glm::vec3> vtxs, std::vector<std::array<int, 3>> faces) :
	vtxs_(std::move(vtxs)),
	faces_(std::move(faces))
{
}

Mesh::~Mesh()
{
}

void Mesh::normalize()
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
	double max_range = maxs[0] - mins[0];
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
		auto defined_face = false;

		sstream >> entity_type;

		switch (entity_type)
		{

		case 'v': {

			double x = 0, y = 0, z = 0;
			if (!(sstream >> x >> y >> z))
			{
				throw domain_error("vertex format invalid");
			}

			vtxs.emplace_back(x, y, z);
			break;
		}
		case 'f': {
			defined_face = true;
			int v1_ind = 0, v2_ind = 0, v3_ind;

			if (!(sstream >> v1_ind >> v2_ind >> v3_ind))
			{
				throw domain_error("face format invalid");
			}

			faces.emplace_back(v1_ind - 1, v2_ind - 1, v3_ind - 1);

			break;
		}
		default: {
			break;
		}
		}
	}

	return Mesh(vtxs, faces);
}

