
/* 
 * File:   Circle.h
 * Author: lidia
 *
 * Created on 8 de febrero de 2021, 19:32
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"
#include "PolygonGeo.h"

class Circle {

private:
	Point _c; // centro
	double _r;  //radio

public:
	/**
	*	@brief Default constructor. Coordinates are initialized with an invalid value.
	*/
	Circle (): _c(Point (0,0)), _r(1.0){}
	/**
	//	*	@brief Constructor.
	*/
	Circle(Point &c, double r): _c(c), _r(r){}
	/**
	*	@brief Copy constructor.
	*/
	Circle (const Circle& orig): _c(orig._c), _r(orig._r){}  ;
	
	/**
	*	@brief Destructor.
	*/
	
	
	virtual ~Circle();

	/**
	 * 
	 * @param p
	 * @return true if p is inside the circle 
	 */
	
	bool isInside (Point &p);
	
	/**
	 * 
	 * @return a PolygonGeo with circular shape 
	 */
	PolygonGeo getPointsCircle ();
};

#endif /* CIRCLE_H */

