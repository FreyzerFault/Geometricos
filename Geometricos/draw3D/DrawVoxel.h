#pragma once

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

