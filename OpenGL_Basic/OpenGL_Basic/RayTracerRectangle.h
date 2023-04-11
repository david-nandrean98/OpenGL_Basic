#pragma once

#include "Mesh.h"

namespace graphics
{
	class RayTracerRectangle: public Mesh
	{
	public:
		RayTracerRectangle();
		RayTracerRectangle(const RayTracerRectangle& other) = delete;
		RayTracerRectangle(RayTracerRectangle&& other);
		void draw() const override;
	};
}