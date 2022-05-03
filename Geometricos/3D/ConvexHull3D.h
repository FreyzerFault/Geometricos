#pragma once
#include <string>
#include "TriangleModel.h"

namespace GEO
{
	class ConvexHull3D
	{
	public:

		ConvexHull3D();
		ConvexHull3D(std::string path);
		ConvexHull3D(const TriangleModel& pointCloud);
	};
}
