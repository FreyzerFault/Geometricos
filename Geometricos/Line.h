
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
		
		Line(const Point& a, const Point& b);

		Line(const Point& p, const Vec2D& v);
		
		Line(const Line& s);

		virtual ~Line();

		/**
		*	@brief Distance from a point to this line.
		*/
		double distPoint(const Point& point) const override;

		/**
		*	@brief Checks if a segment line generates a non-proper intersection.
		*/
		bool impSegmentIntersection(const SegmentLine& segment) const override;
		
		/**
		*	@brief Checks if a segment intersects with this line (proper intersection).
		*/
		bool segmentIntersection(const SegmentLine& segment) const override;
		
		// Punto de intersseccion con un segmento, linea o rayo
		Point* intersectionPoint(const SegmentLine& segment) override;
		Point* intersectionPoint(const RayLine& ray) override;
		Point* intersectionPoint(const Line& line) override;

		/**
		*	@brief Checks if the parameter t is valid to obtain a point for a line (it's always valid, we just need to override).
		*/
		bool isTvalid(double t) override { return true; }

		/**
		*	@brief Assignment operator.
		*/
		virtual Line& operator=(const Line& line);

		/**
		*	@brief Shows some information about the line.
		*/
		virtual void out();

	};

}


#endif /* LINE_H */

