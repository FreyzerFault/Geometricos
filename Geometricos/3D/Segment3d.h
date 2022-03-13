#pragma once

#include "Edge3D.h"

namespace GEO
{
	class Segment3D : public Edge3D
	{
	protected:
		bool isTvalid(double t) const override { return t >= 0.0 && t <= 1.0; }

	public:
		Segment3D(const Vec3D& orig, const Vec3D& dest);
		
		Segment3D(const Segment3D& segment) = default;

		~Segment3D() override = default;
		
		Segment3D& operator=(const Segment3D& segment);

		void out() override;
	};

}

