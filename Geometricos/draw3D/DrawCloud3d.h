#pragma once

#include "Scene.h"
#include "PointCloud3D.h"
#include "Draw.h"


namespace GEO
{
	class DrawVec3D;
	class DrawPoint;

	class DrawCloud3D : public Draw {

		PointCloud3D pc;

		std::vector<DrawVec3D> drawPoints;

	public:


		DrawCloud3D(const PointCloud3D& pointCloud);

		DrawCloud3D(const DrawCloud3D& ddt) : Draw(), pc(ddt.pc) {}


		void drawIt();
		void drawIt(TypeColor c);

		~DrawCloud3D() override = default;
	};
}

