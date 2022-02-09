
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "PointCloud.h"


PointCloud::PointCloud()
{
}

PointCloud::PointCloud(int size, float max_x, float max_y)
{
	//XXXX
}

PointCloud::PointCloud(const std::string& filename)
{
		//XXXX
}

PointCloud::~PointCloud()
{
}

void PointCloud::addPoint(Point& p)
{
	_points.push_back(p);
}

Point PointCloud::centralPoint()
{
	//XXXX
    return Point();
}

void PointCloud::deletePoint(int index)
{
	if (index < _points.size())
	{
		_points.erase(_points.begin() + index);
	}
}



Point PointCloud::getPoint(int position)
{
	if ((position >= 0) && (position < _points.size())) 
	{
		return _points[position];
	}

	return Point();
}

PointCloud & PointCloud::operator=(const PointCloud& pointCloud)
{
	if (this != &pointCloud)
	{
		this->_points = pointCloud._points;
	}

	return *this;
}

void PointCloud::save(const std::string& filename)
{
		//XXXX
}