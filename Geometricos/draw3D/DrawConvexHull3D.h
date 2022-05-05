#pragma once
#include "ConvexHull3D.h"

namespace GEO
{
	class DrawConvexHull3D
	{
		ConvexHull3D convexHull;

		Draw* drawTriangles;
		Draw* drawLines;
	public:

		DrawConvexHull3D(const ConvexHull3D& convexHull);
		DrawConvexHull3D(const DrawConvexHull3D& orig) : convexHull(orig.convexHull) {}
		std::pair<GEO::Draw*, GEO::Draw*> drawIt() const;
		std::pair<GEO::Draw*, GEO::Draw*> drawIt(TypeColor triColor, TypeColor lineColor) const;
		~DrawConvexHull3D() = default;

	};
}
