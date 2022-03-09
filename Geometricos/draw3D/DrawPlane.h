
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
		
		void drawIt(TypeDraw typeDraw = TypeDraw::PLAIN);
		void drawIt(TypeColor c);
		void drawIt(TypeColor c, TypeDraw typeDraw);

		~DrawPlane() override = default;;
	};
}

