#pragma once

#include "Mesh.h"
#include <glm/glm.hpp>
#include <vector>

namespace graphics
{
	class Camera;

	class TriMesh: public Mesh
	{
	public:
		TriMesh(const std::vector<Vertex>& vert, const std::vector<GLuint>& ind);
		TriMesh(const TriMesh& other) = delete;
		TriMesh(TriMesh&& other);
		void draw() const override;
	};
}