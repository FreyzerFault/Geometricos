
#include <iostream>
#include "Edge3d.h"


GEO::Edge3d::Edge3d()
{
}

GEO::Edge3d::Edge3d(Vec3D & orig, Vec3D & dest)
	: _orig(orig), _dest(dest)
{
}

GEO::Edge3d::Edge3d(const Edge3d & edge)
{
	_orig = edge._orig;
	_dest = edge._dest;
}

GEO::Edge3d::~Edge3d()
{
}

GEO::Vec3D GEO::Edge3d::getDestination()
{
	return _dest;
}

GEO::Vec3D GEO::Edge3d::getOrigin()
{
	return _orig;
}

GEO::Vec3D GEO::Edge3d::getPoint(double t)
{
	if (!isTvalid(t)) return Vec3D();
		Vec3D aux1 = _dest.sub(_orig);
		Vec3D aux2 = aux1.scalarMul(t);

	return Vec3D(_orig.add(aux2));
}

std::vector<double> GEO::Edge3d::getVertices()
{
	std::vector<double> vertices;
	std::vector<double> origVertices = _orig.getVector(), destVertices = _dest.getVector();
	vertices.insert(vertices.end(), origVertices.begin(), origVertices.end());
	vertices.insert(vertices.end(), destVertices.begin(), destVertices.end());

	return vertices;
}

GEO::Edge3d & GEO::Edge3d::operator=(const Edge3d & edge)
{
	_orig = edge._orig;
	_dest = edge._dest;

	return *this;
}

void GEO::Edge3d::out()
{
	std:: cout << "Edge->Origin: ";
	_orig.out();
	std::cout << "Edge->Destination: ";
	_dest.out();
}
