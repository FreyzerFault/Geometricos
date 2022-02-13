
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "PointCloud.h"


GEO::PointCloud::PointCloud()
{
}

GEO::PointCloud::PointCloud(int size, float max_x, float max_y)
{
	//XXXX
}

GEO::PointCloud::PointCloud(const std::string& filename)
{
		//XXXX
}

GEO::PointCloud::~PointCloud()
{
}

void GEO::PointCloud::addPoint(Point& p)
{
	_points.push_back(p);
}

GEO::Point GEO::PointCloud::centralPoint()
{
	//XXXX
    return Point();
}

void GEO::PointCloud::deletePoint(int index)
{
	if (index < _points.size())
	{
		_points.erase(_points.begin() + index);
	}
}


GEO::Point GEO::PointCloud::getPoint(int position)
{
	if ((position >= 0) && (position < _points.size())) 
	{
		return _points[position];
	}

	return Point();
}

GEO::PointCloud & GEO::PointCloud::operator=(const PointCloud& pointCloud)
{
	if (this != &pointCloud)
	{
		this->_points = pointCloud._points;
	}

	return *this;
}

void GEO::PointCloud::save(const std::string& filename)
{
		//XXXX
}