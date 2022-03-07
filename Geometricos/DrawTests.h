#pragma once

#include "InclGeom2D.h"
#include "InclGeom3D.h"
#include "InclDraw2D.h"
#include "InclDraw3D.h"

namespace GEO
{
	class DrawTests
	{
		std::vector<Draw*> drawPointers;

	public:
		void drawPolygon2D();
		void drawTriangle2D();
		void drawLines2D();
		void drawPointCloud2D();
		void drawBezier2D();
		void drawLineIntersections2D();


		void drawVaca();

		void clear();

		template <typename T, typename D>
		void drawIt(const T& item, TypeColor color);

		void draw3DModel(const TriangleModel& model);
	};

	template <typename T, typename D>
	void DrawTests::drawIt(const T& item, TypeColor color)
	{
		drawPointers.push_back(new D(item));
		dynamic_cast<D*>(drawPointers[drawPointers.size() - 1])->drawIt(color);
	}
}
