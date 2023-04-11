#include "graphics_utils.h"
#include "StringManipulation.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

namespace graphics
{
	const char* ToString(const FileFormat3D format)
	{
		switch (format)
		{
			case FileFormat3D::DAE:  return "DAE";
			case FileFormat3D::DS3:  return "3DS";
			case FileFormat3D::FBX:  return "FBX";
			case FileFormat3D::MAX:  return "MAX";
			case FileFormat3D::MF3:  return "3MF";
			case FileFormat3D::OBJ:  return "OBJ";
			case FileFormat3D::STL:  return "STL";
			case FileFormat3D::STP:  return "STP";
			case FileFormat3D::VRML: return "VRML";
			case FileFormat3D::X3D:  return "X3D";
			default: return "Unknown";
		}
	}
	// Only works for trimesh
	void MeshLoader::loadOBJ(const char* filename,  /*out*/ std::vector<Vertex>& vertices, /*out*/ std::vector<GLuint>& indices)
	{

		vertices.clear();
		indices.clear();

		std::ifstream in(filename);
		std::string line;

		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec3> temp_normals;
		std::vector<glm::vec2> temp_textures;

		while (std::getline(in, line, '\n'))
		{
			if (line[0] == '#') continue;
			else if (line.substr(0, 2) == "v ")
			{
				std::istringstream is(line.substr(2, line.size() - 1));
				glm::vec3 vertex;
				is >> vertex.x >> vertex.y >> vertex.z;
				temp_vertices.push_back(vertex);
			}
			else if (line.substr(0, 3) == "vn ")
			{
				std::istringstream is(line.substr(3, line.size() - 2));
				glm::vec3 normal;
				is >> normal.x >> normal.y >> normal.z;
				temp_normals.push_back(normal);
			}
			else if (line.substr(0, 3) == "vt ")
			{
				std::istringstream is(line.substr(3, line.size() - 2));
				glm::vec2 texture;
				is >> texture.x >> texture.y;
				temp_textures.push_back(texture);
			}
			else if (line.substr(0, 2) == "f ")
			{
				std::istringstream is(line.substr(2, line.size() - 1));
				while (std::getline(is, line, ' '))
				{
					const auto num = std::count(line.begin(), line.end(), '/');
					Vertex v;
					if (num == 0)
					{
						v.position = temp_vertices[std::atoi(line.c_str()) - 1];
					}
					else
					{
						std::istringstream iss(line);
						std::string v_line;
						std::getline(iss, v_line, '/');
						v.position = temp_vertices[std::atoi(v_line.c_str()) - 1];
						if (num == 1)
						{
							std::getline(iss, v_line, '/');
							v.texCoord = temp_textures[std::atoi(v_line.c_str()) - 1];
						}
						else if (num == 2)
						{
							std::getline(iss, v_line, '/');
							v.texCoord = temp_textures[std::atoi(v_line.c_str()) - 1];
							std::getline(iss, v_line, '/');
							v.normal = temp_normals[std::atoi(v_line.c_str()) - 1];
						}
					}
					auto it = std::find(vertices.begin(), vertices.end(), v);
					if (it == vertices.end())
					{
						vertices.push_back(v);
						indices.push_back(vertices.size() - 1);
					}
					else
					{
						size_t idx = it - vertices.begin();
						indices.push_back(idx);
					}

				}
			}
		}
	}
	void ParametricSurfaceConstructor::construct(const int resolution, glm::vec3(*surface)(float, float), std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
	{
		vertices.clear();
		indices.clear();

		vertices.resize((resolution + 1) * (resolution + 1));

		for (int i = 0; i <= resolution; i++)
		{
			const float u = static_cast<float>(i) / static_cast<float>(resolution);
			for (int j = 0; j <= resolution; j++)
			{
				const float v = static_cast<float>(j) / static_cast<float>(resolution);
				const auto position = surface(u, v);
				int idx = i * (resolution + 1) + j;
				vertices[idx].position = position;
				vertices[idx].texCoord = glm::vec2(u, v);
				const auto du = surface(u + 0.01f, v) - surface(u, v);
				const auto dv = surface(u, v + 0.01f) - surface(u, v);
				vertices[idx].normal = glm::normalize(glm::cross(du, dv));
			}
		}

		indices.resize(resolution * resolution * 6);

		for (int i = 0; i < resolution; i++)
		{
			
			for (int j = 0; j < resolution; j++)
			{
				int idx = (i * resolution + j) * 6;
				indices[idx] = i * (resolution + 1) + j;
				indices[idx + 1] = i * (resolution + 1) + j + 1;
				indices[idx + 2] = (i + 1) * (resolution + 1) + j;
				indices[idx + 3] = i * (resolution + 1) + j + 1;
				indices[idx + 4] = (i + 1) * (resolution + 1) + j + 1;
				indices[idx + 5] = (i + 1) * (resolution + 1) + j;
			}
		}
	}

	void ParametricSurfaceConstructor::construct(const int resolution, glm::vec3(*surface)(float, float), glm::vec3(*normal)(float, float), std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
	{
		vertices.clear();
		indices.clear();

		vertices.resize((resolution + 1) * (resolution + 1));

		for (int i = 0; i <= resolution; i++)
		{
			const float u = static_cast<float>(i) / static_cast<float>(resolution);
			for (int j = 0; j <= resolution; j++)
			{
				const float v = static_cast<float>(j) / static_cast<float>(resolution);
				const auto position = surface(u, v);
				int idx = i * (resolution + 1) + j;
				vertices[idx].position = position;
				vertices[idx].texCoord = glm::vec2(u, v);
				vertices[idx].normal = normal(u, v);
			}
		}

		indices.resize(resolution * resolution * 6);

		for (int i = 0; i < resolution; i++)
		{

			for (int j = 0; j < resolution; j++)
			{
				int idx = (i * resolution + j) * 6;
				indices[idx] = i * (resolution + 1) + j;
				indices[idx + 1] = i * (resolution + 1) + j + 1;
				indices[idx + 2] = (i + 1) * (resolution + 1) + j;
				indices[idx + 3] = i * (resolution + 1) + j + 1;
				indices[idx + 4] = (i + 1) * (resolution + 1) + j + 1;
				indices[idx + 5] = (i + 1) * (resolution + 1) + j;
			}
		}
	}

	glm::vec3 ParametricSurfaceConstructor::Surface::Sphere(float u, float v)
	{
		u *= 2.0f * M_PI;
		v *= M_PI;
		return glm::vec3(std::sin(v) * std::cos(u), std::cos(v), std::sin(v) * std::sin(u));
	}

	glm::vec3 ParametricSurfaceConstructor::Surface::Cylinder(float u, float v)
	{
		return glm::vec3(u, std::cos(v), std::sin(u));
	}

	glm::vec3 ParametricSurfaceConstructor::Normal::Sphere(float u, float v)
	{
		u *= 2.0f * M_PI;
		v *= M_PI;
		return glm::vec3(std::sin(v) * std::cos(u), std::cos(v), std::sin(v) * std::sin(u));
	}




}