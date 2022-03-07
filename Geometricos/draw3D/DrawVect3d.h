#pragma once

#include "Scene.h"
#include "Vec3D.h"
#include "Draw.h"

namespace GEO
{
	class DrawVect3d : public Draw {
		Vec3D dp;
	public:

		DrawVect3d(const Vec3D& p);
		DrawVect3d(const DrawVect3d& ddp) : Draw(), dp(ddp.dp) {}
		void drawIt();
		void drawIt(TypeColor c);
		~DrawVect3d() override = default;;
	};
}

