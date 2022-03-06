#pragma once

#include "Edge3D.h"

namespace GEO
{
	class Segment3d : public Edge3D
	{
	protected:
		bool isTvalid(double t) const override { return t >= 0.0 && t <= 1.0; }

	public:
		Segment3d(const Vec3D& orig, const Vec3D& dest);
		
		Segment3d(const Segment3d& segment) = default;

		~Segment3d() override = default;
		
		Segment3d& operator=(const Segment3d& segment);

		void out() override;
	};

}

