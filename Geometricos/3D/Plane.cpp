
#include <iostream>
#include "Plane.h"
#include "BasicGeom.h"


GEO::Plane::Plane(const Vec3D& p, const Vec3D& u, const Vec3D& v, bool arePoints)
	: _a(p), _b(arePoints ? u : (p + u)), _c(arePoints ? v : (p + v))
{
	if (_a.collinear(_b,_c))
	{
		std::cout << "Se ha definido un plano INVALIDO con 3 puntos colineares:" << std::endl;
		this->out();
	}

}

GEO::Plane::Plane(const Vec3D& p, const Vec3D& normal)
{
	const Vec3D n = normal.normalize();
	// Vector cualquiera que no sea paralelo a la normal
	Vec3D arbitrario(1,0,0);
	if (arbitrario == n || arbitrario == -n)
		arbitrario.setVec(0, 1, 0);

	// Cualquiera perpendicular a la normal es un vector del plano
	const Vec3D v0 = arbitrario.cross(n);
	const Vec3D v1 = v0.cross(n);

	_a = p;
	_b = _a + v0;
	_c = _a + v1;
}

bool GEO::Plane::coplanar(const Vec3D& p) const
{
	// La distancia a p es nula
	return distance(p) <= BasicGeom::EPSILON; // n · v == 0
}

double GEO::Plane::distance(const Vec3D& p) const
{
	// Cualquier vector Plano -> p
	const Vec3D v = p - _a;
	const Vec3D n = getNormal();

	// La distancia de la proyeccion de v sobre n
	// d = v · n / |n| (n esta normalizado)
	return v.dot(n);
}

double GEO::Plane::getA() const
{
	return (BasicGeom::determinant2x2(_c.getZ() - _a.getZ(), _c.getY() - _a.getY(), _b.getY() - _a.getY(), _b.getZ() - _a.getZ()));
}

double GEO::Plane::getB() const
{
	return (BasicGeom::determinant2x2(_c.getX() - _a.getX(), _c.getZ() - _a.getZ(), _b.getZ() - _a.getZ(), _b.getX() - _a.getX()));
}

double GEO::Plane::getC() const
{
	return (BasicGeom::determinant2x2(_c.getY() - _a.getY(), _c.getX() - _a.getX(), _b.getX() - _a.getX(), _b.getY() - _a.getY()));
}

double GEO::Plane::getD() const
{
	return -(getA() * _a.getX() + getB() * _a.getY() + getC() * _a.getZ());
}

GEO::Vec3D GEO::Plane::getNormal() const
{
	return getV().cross(getU()).normalize();
}

bool GEO::Plane::intersect(const Line3D& line, Vec3D& point) const
{
	const Vec3D n = getNormal();
	const Vec3D ab = line.getDest() - line.getOrig();

	// Si la Linea es Perpendicular a la Normal, son paralelos
	if (BasicGeom::equal(n.dot(ab), 0))
		return false;
	
	const Vec3D ac = getP() - line.getOrig();

	const double t = - (n.dot(ac) / n.dot(ab));

	point = line.getPoint(t);

	return true;
}

bool GEO::Plane::intersect(const Plane & plane, Line3D & line) const
{
	const Vec3D n = getNormal().normalize();

	// Si las normales son Paralelas, no intersectan
	if (BasicGeom::equal(n.dot(plane.getNormal()), 1))
	return false;

	// Vector de la interseccion
	const Vec3D v = n.cross(plane.getNormal()).normalize();

	// Linea en el plano perpendicular a la interseccion
	const Vec3D perp = v.cross(n).normalize();
	
	// Punto de interseccion de la linea perpendicular a la interseccion y la normal
	// Me da un punto en mi linea de interseccion para crearla
	const Line3D perpLine(getP(), getP() + perp);
	Vec3D p;
	plane.intersect(perpLine, p);
	
	line = Line3D(p, p + v);

	return true;
}


bool GEO::Plane::intersect(const Plane& pa, const Plane& pb, Vec3D& point) const
{
	Line3D intersLine;

	// Interseccion plano-plano
	if (!pa.intersect(pb, intersLine))
		return false;

	// Interseccion linea-plano
	if (!intersect(intersLine, point))
		return false;

	return true;
}

GEO::Plane & GEO::Plane::operator=(const Plane & plane)
{
	if (this != &plane)
	{
		_a = plane._a;
		_b = plane._b;
		_c = plane._c;
	}

	return *this;
}

void GEO::Plane::out()
{
	std::cout << "Plane->a: ";
	_a.out();
	std::cout <<"Plane->b: ";
	_b.out();
	std::cout <<"Plane->c: ";
	_c.out();
}