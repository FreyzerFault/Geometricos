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
		/**
		*	@brief Constructor of a rayline given its two points.
		*/
		RayLine(const Point& a, const Point& b);

		/**
		*	@brief Copy constructor.
		*/
		RayLine(const RayLine& s);

		/**
		*	@brief Destructor.
		*/
		~RayLine();

		/**
		*	@brief Distance from a point defined by 'vector' to this rayline.
		*/
		double distPoint(const Point& point) const override;

		/**
		*	@brief Checks if this rayline intersects with a segment in a non-proper way.
		*/
		bool impSegmentIntersection(const SegmentLine& segment) const override;

		bool segmentIntersection(const SegmentLine& segment) const override;

		
		// Punto de intersseccion con un segmento, linea o rayo
		Point* intersectionPoint(const SegmentLine& segment) override;
		Point* intersectionPoint(const RayLine& ray) override;
		Point* intersectionPoint(const Line& line) override;

		/**
		*	@brief Checks if the parameter t is valid to get a point of the rayline.
		*/
		bool isTvalid(double t) const override { return t >= BasicGeom::CERO; }

		/**
		*	@brief Assignment operator.
		*/
		virtual RayLine& operator=(const RayLine& rayline);

		/**
		*	@brief Shows some information about the rayline in the debug dialog.
		*/
		virtual void out();
	};

}


#endif /* RAYLINE_H */

