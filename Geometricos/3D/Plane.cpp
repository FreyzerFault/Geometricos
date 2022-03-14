
#include <iostream>
#include "Plane.h"
#include "BasicGeom.h"


GEO::Plane::Plane(const Vec3D& p, const Vec3D& u, const Vec3D& v, bool arePoints)
	: _s(p), _r(arePoints ? u : (p + u)), _t(arePoints ? v : (p + v))
{
	if (_s.collinear(_r,_t))
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

	_s = p;
	_r = _s + v0;
	_t = _s + v1;
}

bool GEO::Plane::coplanar(const Vec3D& p) const
{
	// La distancia a p es nula
	return distance(p) <= BasicGeom::EPSILON; // n · v == 0
}

double GEO::Plane::distance(const Vec3D& p) const
{
	// Cualquier vector Plano -> p
	const Vec3D v = p - _s;
	const Vec3D n = getNormal();

	// La distancia de la proyeccion de v sobre n
	// d = v · n / |n| (n esta normalizado)
	return v.dot(n);
}

double GEO::Plane::getA() const
{
	return getNormal().getX();
	//return BasicGeom::det2x2(_t.getZ() - _s.getZ(), _t.getY() - _s.getY(), _r.getY() - _s.getY(), _r.getZ() - _s.getZ());
}

double GEO::Plane::getB() const
{
	return getNormal().getY();
	//return BasicGeom::det2x2(_t.getX() - _s.getX(), _t.getZ() - _s.getZ(), _r.getZ() - _s.getZ(), _r.getX() - _s.getX());
}

double GEO::Plane::getC() const
{
	return getNormal().getZ();
	//return BasicGeom::det2x2(_t.getY() - _s.getY(), _t.getX() - _s.getX(), _r.getX() - _s.getX(), _r.getY() - _s.getY());
}

double GEO::Plane::getD() const
{
	return -(getA() * _s.getX() + getB() * _s.getY() + getC() * _s.getZ());
}

GEO::Vec3D GEO::Plane::getNormal() const
{
	return getV().cross(getU()).normalize();
	//return {getA(), getB(), getC()};
}

bool GEO::Plane::intersect(const Line3D& line, Vec3D& point) const
{
	const Vec3D n = getNormal();
	const Vec3D v = line.getDest() - line.getOrig();

	// Si la Linea es Perpendicular a la Normal, son paralelos
	if (BasicGeom::equal(n.dot(v), 0))
		return false;

	const double t = - ((n.dot(line.getOrig()) + getD()) / n.dot(v));

	point = line.getPoint(t);

	return true;
}

bool GEO::Plane::intersect(const Plane& plane, Line3D& line) const
{
	const Vec3D n = getNormal();

	// Si las normales son Paralelas, no intersectan
	if (BasicGeom::equal(n.dot(plane.getNormal()), 1))
		return false;

	// Implementacion propia a partir de la perpendicular de la perpendicular,
	// que deberia de intersectar uno de los planos y pertenece al otro plano,
	// por lo que el punto de interseccion seria un punto de la linea que buscamos

	//// Vector de la interseccion
	//const Vec3D v = n.cross(plane.getNormal()).normalize();

	//// Linea en el plano perpendicular a la interseccion
	//const Vec3D perp = v.cross(n).normalize();
	//
	//// Punto de interseccion de la linea perpendicular a la interseccion y la normal
	//// Me da un punto en mi linea de interseccion para crearla
	//const Line3D perpLine(getP(), getP() + perp);
	//Vec3D p;
	//plane.intersect(perpLine, p);
	//
	//line = Line3D(p, p + v);

	
	const Vec3D n1 = getNormal();
	const Vec3D n2 = plane.getNormal();
	const Vec3D n3 = n1.cross(n2).normalize();

	const double a1 = n1.getX(), b1 = n1.getY(), c1 = n1.getZ(), d1 = getD();
	const double a2 = n2.getX(), b2 = n2.getY(), c2 = n2.getZ(), d2 = plane.getD();
	const double a3 = n3.getX(), b3 = n3.getY(), c3 = n3.getZ();

	const double DET = BasicGeom::det3x3(a1, b1, c1, a2, b2, c2, a3, b3, c3);

	if (BasicGeom::equal(DET, 0))
		return false;

	const double x = d2 * BasicGeom::det2x2(b1, c1, b3, c3)
	- d1 * BasicGeom::det2x2(b2, c2, b3, c3);
	const double y = d2 * BasicGeom::det2x2(a3, c3, a1, c1)
	- d1 * BasicGeom::det2x2(a3, c3, a2, c2);
	const double z = d2 * BasicGeom::det2x2(a1, b1, a3, b3)
	- d1 * BasicGeom::det2x2(a2, b2, a3, b3);

	const Vec3D p(x,y,z);

	line = Line3D(p, p + n3);

	

	// Implementacion de http://paulbourke.net/geometry/pointlineplane/:

	//const double d1 = getD();
	//const double d2 = plane.getD();
	//const double determinant = n1.dot(n1) * n2.dot(n2) - n1.dot(n2) * n1.dot(n2);

	//// A partir de la ecuacion de la linea que buscamos:
	//// p(x,y) = p0 + u * v = c1*n1 + c2*n2 + u(n1 x n2)
	//// Despejamos c1 y c2:
	//const double c1 = (d1 * n2.dot(n2) - d2 * n1.dot(n2)) / determinant;
	//const double c2 = (d2 * n1.dot(n1) - d1 * n1.dot(n2)) / determinant;

	//const Vec3D p = n1 * c1 + n2 * c2;
	//const Vec3D v = n1.cross(n2);

	//line = Line3D(p, p + v);

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
		_s = plane._s;
		_r = plane._r;
		_t = plane._t;
	}

	return *this;
}

void GEO::Plane::out()
{
	std::cout << "Plane->a: ";
	_s.out();
	std::cout <<"Plane->b: ";
	_r.out();
	std::cout <<"Plane->c: ";
	_t.out();
}