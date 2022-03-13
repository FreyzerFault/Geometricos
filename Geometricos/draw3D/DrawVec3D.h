#pragma once

#include "Scene.h"
#include "Vec3D.h"
#include "Draw.h"

namespace GEO
{
	class DrawVec3D : public Draw {
		Vec3D dp;
	public:

		DrawVec3D(const Vec3D& p);
		DrawVec3D(const DrawVec3D& ddp) : Draw(), dp(ddp.dp) {}

		void drawIt();
		void drawIt(TypeColor c);
		~DrawVec3D() override = default;;
	};
}

