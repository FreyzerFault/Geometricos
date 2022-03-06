
#include <iostream>
#include "Edge3D.h"

#include "Line3D.h"


bool GEO::Edge3D::isTvalid(double t) const
{
	return t >= 0 && t <= 1;
}

double GEO::Edge3D::getNearestT(const Vec3D& p) const
{
	const Vec3D v = _dest - _orig;
	const double t = v.dot(p - _orig) / v.dot(v);

	if (this->isTvalid(t))
		return t;

	// Al ser un segmento, su t mas cercana sera 0 o 1
	if (t < 0)
		return 0;

	return 1;
}

GEO::Vec3D GEO::Edge3D::getNearestPoint(const Vec3D& p) const
{
	return getPoint(getNearestT(p));
}

GEO::Edge3D::Edge3D(const Vec3D& orig, const Vec3D& dest)
	: _orig(orig), _dest(dest)
{
}

GEO::Vec3D GEO::Edge3D::getPoint(double t) const
{
	// Invalido si t < 0 o t > 1
	if (!isTvalid(t)) return {};
	
	return {_orig + (_dest - _orig) * t};
}

double GEO::Edge3D::distance(const Vec3D& p) const
{
	return (getNearestPoint(p) - p).module();
}

GEO::Vec3D GEO::Edge3D::normal(const Vec3D& p) const
{
	const Vec3D v = _dest - _orig;
	const double t = v.dot(p - _orig) / v.dot(v);
	
	return (p - (_orig + v * t)).normalize();
}


std::vector<double> GEO::Edge3D::getVertices() const
{
	std::vector<double> vertices;
	std::vector<double> origVertices(_orig.getVector()), destVertices(_dest.getVector());
	vertices.insert(vertices.end(), origVertices.begin(), origVertices.end());
	vertices.insert(vertices.end(), destVertices.begin(), destVertices.end());

	return vertices;
}

void GEO::Edge3D::out()
{
	std:: cout << "Edge->Origin: ";
	_orig.out();
	std::cout << "Edge->Destination: ";
	_dest.out();
}
