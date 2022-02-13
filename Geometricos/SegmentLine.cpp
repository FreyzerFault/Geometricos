#include <cmath>
#include <iostream>
#include "SegmentLine.h"
#include "Line.h"
#include "RayLine.h"


GEO::SegmentLine::SegmentLine()
{
}

GEO::SegmentLine::SegmentLine(const Point& a, const Point& b)
	: _orig(a), _dest(b)
{
}

GEO::SegmentLine::SegmentLine(const SegmentLine& segment)
	: _orig(segment._orig), _dest(segment._dest)
{
}

GEO::SegmentLine::SegmentLine(double ax, double ay, double bx, double by)
	: _orig(ax, ay), _dest(bx, by)
{
}

GEO::SegmentLine::~SegmentLine()
{
}


GEO::SegmentLine & GEO::SegmentLine::operator=(const SegmentLine & segment)
{
	if (this != &segment)
	{
		this->_orig = segment._orig;
		this->_dest = segment._dest;
	}

	return *this;
}



bool GEO::SegmentLine::distinct(SegmentLine & segment)
{
	return !equal(segment);
}



bool GEO::SegmentLine::equal(SegmentLine & segment)
{
	return (_orig.equal(segment._orig) && _dest.equal(segment._dest)) || (_orig.equal(segment._dest) && _dest.equal(segment._orig));
}

GEO::Point GEO::SegmentLine::getPoint(double t)
{

	//XXXX
	return Point();
}


bool GEO::SegmentLine::impSegmentIntersection(SegmentLine& segment)
{
//XXXX
	return true;
}

bool GEO::SegmentLine::isHorizontal()
{
	return true;
}




bool GEO::SegmentLine::isVertical()
{
	//XXXX
	return true; 
}


double GEO::SegmentLine::slope()
{
	//XXXX
	
	return 0;
}




 // PROTECTED METHODS



void GEO::SegmentLine::out()
{
	std::cout << "Point A: )";
	_orig.out();
	std::cout << "Point B: ";
	_dest.out();
}



