#pragma once

#include "Vec2D.h"

namespace GEO
{
	class Triangle
	{
		Vec2D a, b, c;

	public:
		friend class DrawTriangle; //evitar
		
		Triangle(const Vec2D& aa, const Vec2D& bb, const Vec2D& cc);
		
		Triangle(const Triangle& t) = default;
		
		Vec2D getA() const { return a; }
		Vec2D getB() const { return b; }
		Vec2D getC() const { return c; }
	};
}
