#pragma once

#include "Scene.h"
#include "Vec3D.h"
#include "Draw.h"
#include "DrawAABB.h"
#include "Voxel.h"

namespace GEO
{
	class DrawVoxel : public DrawAABB {
		Voxel voxel;
	public:

		DrawVoxel(const Voxel& voxel);

		void drawIt();
		~DrawVoxel() override = default;
	};
}

