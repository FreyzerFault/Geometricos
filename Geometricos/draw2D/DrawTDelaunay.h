#pragma once
#include "Draw.h"
#include "DrawTriangleModel.h"
#include "TDelaunay.h"

namespace GEO
{
	class DrawTDelaunay
	{
		TDelaunay delaunay;

		Draw* drawTriangles;
		Draw* drawLines;
	public:

		DrawTDelaunay(const TDelaunay& delaunay);
		DrawTDelaunay(const DrawTDelaunay& orig) : delaunay(orig.delaunay) {}
		std::pair<GEO::Draw*, GEO::Draw*> drawIt() const;
		std::pair<GEO::Draw*, GEO::Draw*> drawIt(TypeColor triColor, TypeColor lineColor) const;
		~DrawTDelaunay() = default;

	};
}
