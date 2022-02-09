
/* 
 * File:   Line.h
 * Author: lidia
 *
 * Created on 18 de enero de 2021, 19:39
 */

#ifndef LINE_H
#define LINE_H

#include "SegmentLine.h"


class Line : public SegmentLine
{
public:
	/**
	*	@brief Constructor.
	*/
	Line(const Point& a, const Point& b);

	/**
	*	@brief Copy constructor.
	*/
	Line(const Line& s);

	/**
	*	@brief Destructor.
	*/
	virtual ~Line();

	/**
	*	@brief Distance from a point defined by 'vector' to this line.
	*/
	double distPointLine(Vect2d& v);

	/**
	*	@brief Checks if the specified line intersects with this one.
	*	@param intersection If both lines intersect, then this point is the intersection. Otherwise this point is not valid.
	*/
	//virtual bool intersects(Line& line, Vect2d& intersection);

	/**
	*	@brief Checks if the specified rayline intersects with this line.
	*	@param intersection If rayline and line intersect, then this point is the intersection. Otherwise this point is not valid.
	*/
	//virtual bool intersects(RayLine& rayline, Vect2d& intersection);

	/**
	*	@brief Checks if the specified segment intersects with this line.
	*	@param intersection If line and segment intersect, then this point is the intersection. Otherwise this point is not valid.
	*/
	//virtual bool intersects(SegmentLine& segment, Vect2d& intersection);

	/**
	*	@brief Checks if a segment line generates a non-proper intersection.
	*/
	bool impSegmentIntersection(SegmentLine& l);

	/**
	*	@brief Checks if the parameter t is valid to obtain a point for a line (it's always valid, we just need to override).
	*/
	virtual bool isTvalid(double t) { return true; }

	/**
	*	@brief Assignment operator.
	*/
	virtual Line& operator=(const Line& line);

	/**
	*	@brief Shows some information about the line.
	*/
	virtual void out();

	/**
	*	@brief Checks if a segment intersects with this line (proper intersection).
	*/
	bool segmentIntersection(SegmentLine& l);
};



#endif /* LINE_H */

