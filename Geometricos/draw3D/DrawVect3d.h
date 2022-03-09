#pragma once

#include "Scene.h"
#include "Vec3D.h"
#include "Draw.h"

namespace GEO
{
	class DrawVect3D : public Draw {
		Vec3D dp;
	public:

		DrawVect3D(const Vec3D& p);
		DrawVect3D(const DrawVect3D& ddp) : Draw(), dp(ddp.dp) {}

		void drawIt();
		void drawIt(TypeColor c);
		~DrawVect3D() override = default;;
	};
}

