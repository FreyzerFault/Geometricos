
/* 
 * File:   SegmentLIne.h
 * Author: lidia
 *
 * Created on 17 de enero de 2021, 17:49
 */

#ifndef SEGMENTLINE_H
#define SEGMENTLINE_H

#include "Point.h"

namespace GEO
{
	class Line;
	class RayLine;

	class SegmentLine {
		
	friend class DrawSegment;

	protected:
		
		Point _orig, _dest; 
		
		// Calcula t0 = Parametro de la recta donde esta el Punto de la recta más cercano a point
		double getDistanceT0(const Point& point) const;
		
		// Punto de interseccion con la linea que contiene c,d, asigna s y t
		Point* intersectionPoint(const Point& c, const Point& d, double& s, double& t) const;

		
	public:

		SegmentLine() = default;

		// A partir de 2 puntos
		SegmentLine(const Point& a, const Point& b);
		SegmentLine(double ax, double ay, double bx, double by);

		SegmentLine(const SegmentLine& segment) = default;
		
		SegmentLine& operator=(const SegmentLine& segment);
		
		virtual ~SegmentLine() = default;

		// Distancia (mas corta) desde un Punto al Segmento
		virtual double distPoint(const Point& point) const;

		// Punto del segmento perteneciente al Parámetro t en la Ecuación Paramétrica
		Point getPoint(double t) const;

		// Comprueba que el parámetro t sea válida en la paramétrica (da un punto contenido en el Segmento)
		virtual bool isTvalid(double t) const;
		
		// Constante de la Ecuación Implícita
		// c = y-mx
		double getEquC() const;

		// LONGITUD del Segmento
		double length() const { return _orig.distPoint(_dest); }

		// PENDIENTE de la recta
		double slope() const;
		
		// Area del Triangulo formado por el segmento y otro punto * 2 (La del cuadrado)
		double triangleArea2(const Point& p) const { return p.triangleArea2(_orig, _dest); }
		

		// ============================= INTERSECCIONES =============================

		// Interseccion propia con otro segmento
		virtual bool segmentIntersection(const SegmentLine& segment) const;
		
		// Intersección impropia con otro segmento (uno de los puntos esta contenido en el otro segmento)
		virtual bool impSegmentIntersection(const SegmentLine& segment) const;

		// Punto de intersseccion con un segmento, linea o rayo
		virtual Point* intersectionPoint(const SegmentLine& segment) const;
		virtual Point* intersectionPoint(const RayLine& ray) const;
		virtual Point* intersectionPoint(const Line& line) const;
		
		// ===========================================================================

		Point getA() const { return _orig; }
		Point getB() const { return _dest; }
		
		void setA(const Point& p) { _orig = p; }
		void setB(const Point& p) { _dest = p; }

		// Comprueba si son distintos o iguales
		bool equal(const SegmentLine& segment) const;
		bool distinct(const SegmentLine& segment) const;

		// Comprobar si es Horizontal o Vertical
		bool isHorizontal() const;
		bool isVertical() const;

		// Comprueba si p esta a la izquierda o a la derecha del Segmento
		bool left(const Point& p) const { return p.left(_orig, _dest); }
		bool right(const Point& p) const { return p.right(_orig, _dest); }



		bool operator==(const SegmentLine& segment) const { return equal(segment); }
		bool operator!=(const SegmentLine& segment) const { return distinct(segment); }

	protected:

		virtual void out();
	};

}



#endif /* SEGMENTLINE_H */

