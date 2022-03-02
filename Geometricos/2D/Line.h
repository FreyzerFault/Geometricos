
/* 
 * File:   Line.h
 * Author: lidia
 *
 * Created on 18 de enero de 2021, 19:39
 */

#ifndef LINE_H
#define LINE_H

#include "SegmentLine.h"

namespace GEO
{
	class Line : public SegmentLine
	{
	public:
		
		Line(const Point& a, const Point& b); // Punto --------> Punto
		Line(const Point& p, const Vec2D& v); // Punto -Vector-> ·
		
		Line(const Line& s) = default;

		~Line() override = default;
		
		// Distancia (mas corta) desde un Punto a la Linea
		double distPoint(const Point& point) const override;
		
		// Comprueba que el parámetro t sea válida en la paramétrica (da un punto contenido en el Segmento)
		bool isTvalid(double t) const override { return true; }

		// Interseccion propia con otro segmento
		bool segmentIntersection(const SegmentLine& segment) const override;
		
		// Intersección impropia con otro segmento (uno de los puntos esta contenido en el otro segmento)
		bool impSegmentIntersection(const SegmentLine& segment) const override;

		
		Line& operator=(const Line& line);

		void out() override;

	};

}


#endif /* LINE_H */

