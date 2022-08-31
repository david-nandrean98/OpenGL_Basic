#include "graphics_utils.h"
#include "StringManipulation.h"
#include <fstream>
#include <string>
#include <sstream>
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

	Mesh MeshLoader::loadOBJ(const char* filename, const char* textureFile)
	{

		std::ifstream in(filename);
		std::string line;

		std::vector<GLfloat> temp_vertices;
		std::vector<GLfloat> temp_normals;
		std::vector<GLfloat> temp_textures;

		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;

		struct Vertex
		{
			Vertex(const std::vector<std::string>& init)
			{
				vertex = std::stoi(init[0]) - 1;
				texture = std::stoi(init[1]) - 1;
				normal = std::stoi(init[2]) - 1;
			}
			bool operator<(const Vertex& other) const
			{
				return this->vertex < other.vertex ? true :
					(this->vertex > other.vertex ? false :
						(this->texture < other.texture ? true : (this->texture > other.texture ? false :
							this->normal < other.normal)));
			}

			bool operator==(const Vertex& other) const
			{
				return this->vertex == other.vertex &&
					   this->texture == other.texture &&
					   this->normal == other.normal;
			}
			size_t vertex;
			size_t texture;
			size_t normal;
		};
		GLuint indexNumber = 0;
		std::map<Vertex, GLuint> vertexIndex;

		while (std::getline(in, line))
		{
			if (line[0] == '#') continue;
			if (line.substr(0, 2) == "v ")
			{
				std::istringstream iss(line.substr(2));
				float x, y, z;
				iss >> x >> y >> z;
				temp_vertices.push_back(x);
				temp_vertices.push_back(y);
				temp_vertices.push_back(z);
			}
			else if (line.substr(0, 3) == "vn ")
			{
				std::istringstream iss(line.substr(3));
				float x, y, z;
				iss >> x >> y >> z;
				temp_normals.push_back(x);
				temp_normals.push_back(y);
				temp_normals.push_back(z);
			}
			else if (line.substr(0, 3) == "vt ")
			{
				std::istringstream iss(line.substr(3));
				float x, y;
				iss >> x >> y;
				temp_textures.push_back(x);
				temp_textures.push_back(y);
			}
			else if (line.substr(0, 2) == "f ")
			{
				std::istringstream iss(line.substr(2));
				std::string first, second, third;
				iss >> first >> second >> third;

				std::vector<Vertex>faceVertices = 
				{ Vertex(core::delimitByToken(first, "/")),
				Vertex(core::delimitByToken(second, "/")),
				Vertex(core::delimitByToken(third, "/")) };

				for (const auto& faceVertex : faceVertices)
				{
					std::map<Vertex, GLuint>::const_iterator it;
					if ((it = vertexIndex.find(faceVertex)) != vertexIndex.cend())
					{
						indices.push_back(it->second);
					}
					else
					{
						indices.push_back(indexNumber);
						vertexIndex.insert({ faceVertex, indexNumber++ });
						
						size_t vInd = 3 * faceVertex.vertex;
						vertices.push_back(temp_vertices[vInd]);
						vertices.push_back(temp_vertices[vInd + 1]);
						vertices.push_back(temp_vertices[vInd + 2]);

						size_t tInd = 2 * faceVertex.texture;
						vertices.push_back(temp_textures[tInd]);
						vertices.push_back(temp_textures[tInd + 1]);

						size_t nInd = 3 * faceVertex.normal;
						vertices.push_back(temp_normals[nInd]);
						vertices.push_back(temp_normals[nInd + 1]);
						vertices.push_back(temp_normals[nInd + 2]);
					}
				}
			}
		}
		return Mesh(vertices, indices, "default.vert", "default.frag", textureFile);
	}
}