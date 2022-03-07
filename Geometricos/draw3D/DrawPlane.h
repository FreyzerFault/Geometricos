
#pragma once

#include "Scene.h"
#include "Plane.h"
#include "Draw.h"

namespace GEO
{
	class DrawPlane : public Draw {

		Plane dt;

	public:

		DrawPlane(const Plane& plane);

		DrawPlane(const DrawPlane& ddt) : Draw(), dt(ddt.dt) {}

		void drawIt();
		void drawIt(TypeColor c);

		~DrawPlane() override = default;;
	};
}

