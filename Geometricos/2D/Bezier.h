#pragma once
#include <vector>

#include "Point.h"

namespace GEO
{
	class Bezier
	{
		std::vector<Point> _points;

	public:
		Bezier();
		Bezier(std::string& filename);

		void addPoint(Point p);
		void addPoint(double x, double y);

		void save(const std::string& filename) const;

		Point getPoint(unsigned int i) const;
		std::vector<Point> getPoints() const { return _points; }
	};
}
