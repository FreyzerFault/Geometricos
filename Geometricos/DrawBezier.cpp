#include "DrawBezier.h"

#include "Scene.h"
#include "SegmentLine.h"
#include "Vec2D.h"

GEO::DrawBezier::DrawBezier(Bezier& bezier)
	: _bezier(&bezier)
{
	// GRADO 3 ==> p(t)= [ (1−t)^3 * p1 ] + [ 3t(1−t)^2 * p2 ] + [ 3t^2(1−t) * p3 ] + [ t^3 * p4 ]

	Point* inicio = &_bezier->getPoint(0);
	Point* final = &_bezier->getPoint(_bezier->getPoints().size() - 1);

	// Primer Vertice
	_vertices.emplace_back(inicio->getX(), inicio->getY(), 0.0);
	_normals.emplace_back(0, 0, 1);
	_indices.push_back ( 0 );

	int index = 0;
	const int n = _bezier->getPoints().size() - 1;

	// Aumentamos un incremento de t a partir del primer punto
	Point puntoIncrementado(*inicio);
	double t = 0;
	while(t <= 1)
	{
		// Punto por cada incremento de t
		Point p(0.0, 0.0);

		// GRADO n ==> p(t) = SUM[i=0,n] ( comb(n , i) * Pi * (1-t)^(n-i) * t^i )
		for (int i = 0; i <= n; ++i)
		{
			const double comb = BasicGeom::combinatoria(n, i);

			Point* pi = &_bezier->getPoint(i);

			// Suma acumulada
			p = p + (*pi * (comb * pow(1 - t, n - i) * pow(t, i)));
		}

		_vertices.emplace_back(p.getX(), p.getY(), 0.0);
		_normals.emplace_back(0, 0, 1);
		_indices.push_back(++index);

		constexpr double incrementoT = 0.02;
		t += incrementoT;
	}
	// Final vertex
	_vertices.emplace_back(final->getX(), final->getY(), 0.0);
	_normals.emplace_back(0, 0, 1);
	_indices.push_back (++index);

	buildVAO ();
}

void GEO::DrawBezier::drawIt()
{
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::LINE );
	Scene::getInstance ()->addModel ( this );
}

void GEO::DrawBezier::drawIt(TypeColor c)
{
	setColorActivo (c);
	drawIt();
}
