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
		//float distPointRayline(Vec2D& vector);

		/**
		*	@brief Checks if this rayline intersects with a segment in a non-proper way.
		*/
		bool impSegmentIntersection(SegmentLine& segment);

		
		// Punto de intersseccion con un segmento, linea o rayo
		Point* intersectionPoint(const SegmentLine& segment) override;
		Point* intersectionPoint(const RayLine& ray) override;
		Point* intersectionPoint(const Line& line) override;

		/**
		*	@brief Checks if the parameter t is valid to get a point of the rayline.
		*/
		virtual bool isTvalid(double t) { return t >= 0; }

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

