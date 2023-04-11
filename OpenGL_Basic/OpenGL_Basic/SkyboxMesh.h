#pragma once

#include "Mesh.h"

namespace graphics
{
	class SkyboxMesh : public Mesh
	{
	public:
		SkyboxMesh();
		SkyboxMesh(const SkyboxMesh& other) = delete;
		SkyboxMesh(SkyboxMesh&& other);
		void draw() const override;
	};
}
