#pragma once
#include "Draw.h"
#include "DrawTriangleModel.h"
#include "TDelaunay.h"

namespace GEO
{
	class DrawTDelaunay
	{
		TDelaunay delaunay;

		DrawTriangleModel* drawTriangles;
	public:

		DrawTDelaunay(const TDelaunay& delaunay);
		DrawTDelaunay(const DrawTDelaunay& orig) : delaunay(orig.delaunay) {}
		void drawIt();
		void drawIt(TypeColor c);
		~DrawTDelaunay() = default;

	};
}
