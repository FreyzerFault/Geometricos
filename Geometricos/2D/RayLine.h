/* 
 * File:   RayLine.h
 * Author: lidia
 *
 * Created on 19 de enero de 2021, 10:12
 */


#ifndef RAYLINE_H
#define RAYLINE_H


#include "SegmentLine.h"


namespace GEO
{
	class RayLine : public SegmentLine
	{

	public:
		RayLine(const Point& a, const Point& b);
		
		RayLine(const RayLine& s) = default;
		
		~RayLine() override = default;
		
		// Distancia (mas corta) desde un Punto al Segmentoline.
		double distPoint(const Point& point) const override;
		
		// Comprueba que el parámetro t sea válida en la paramétrica (da un punto contenido en el Segmento)
		bool isTvalid(double t) const override { return t >= BasicGeom::CERO; }

		// Interseccion propia con otro segmento
		bool segmentIntersection(const SegmentLine& segment) const override;

		// Intersección impropia con otro segmento (uno de los puntos esta contenido en el otro segmento)
		bool impSegmentIntersection(const SegmentLine& segment) const override;


		RayLine& operator=(const RayLine& rayline);

		void out() override;
	};

}


#endif /* RAYLINE_H */

