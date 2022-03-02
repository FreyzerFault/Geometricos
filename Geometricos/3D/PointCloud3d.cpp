#include <cmath>
#include <inttypes.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "BasicGeom.h"
#include "PointCloud3d.h"

#include <glm/ext/scalar_constants.hpp>


GEO::PointCloud3d::PointCloud3d() 
	: _maxPoint(INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY) 
{
}

GEO::PointCloud3d::PointCloud3d (std::vector<Vec3D>& pointCloud):_points(pointCloud),
																  _maxPoint(INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY){}

GEO::PointCloud3d::PointCloud3d(const std::string & filename)
	: _maxPoint(-INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY)
{
	auto splitByComma = [this](std::string& string) -> std::vector<std::string>
	{
		std::stringstream ss(string);
		std::vector<std::string> result;

		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ',');
			result.push_back(substr);
		}

		return result;
	};

	std::string currentLine; 				// Línea actual del fichero.
	std::ifstream inputStream;				// Flujo de entrada.
	inputStream.open(filename.c_str());

	while (std::getline(inputStream, currentLine))
	{
		std::vector<std::string> coord = splitByComma(currentLine);

		if (coord.size() == 3)	
		{
			try {
				Vec3D point(std::stof(coord[0].c_str(), nullptr), std::stof(coord[1].c_str(), nullptr), (std::stof(coord[2].c_str(), nullptr)));
				this->addPoint(point);
			}
			catch (const std::exception& excep)
			{
				inputStream.close();

				throw excep;
			}
		}
	}
	inputStream.close();					// Cerramos fichero.
}

GEO::PointCloud3d::PointCloud3d(int size, float max_x, float max_y, float max_z)
	: _maxPoint(-INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY)
{
	_points = std::vector<Vec3D>();

	while (size > 0)
	{
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_x * 2.0f))) - max_x;
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_y * 2.0f))) - max_y;
		float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_z * 2.0f))) - max_z;
				Vec3D val (x,y,z);
		this->addPoint(val);

		--size;
	}
}

GEO::PointCloud3d::PointCloud3d(int size, float radius)
	: _maxPoint(-INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY)
{
	_points = std::vector<Vec3D>();

	while (size > 0)
	{
		float theta = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)) * 2.0f * glm::pi<float>();
		float phi = std::acos(1.0f - 2.0f * static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)));
		double x = std::sin(phi) * std::cos(theta);
		double y = std::sin(phi) * std::sin(theta);
		double z = std::cos(phi);

		float r = radius * std::sqrt(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)));
		Vec3D point(r * x, r * y, r * z);
		this->addPoint(point);

		--size;
	}
}

GEO::PointCloud3d::PointCloud3d(const PointCloud3d & pointCloud)
	: _points(pointCloud._points), _maxPoint(pointCloud._maxPoint), _minPoint(pointCloud._minPoint)
{
}

GEO::PointCloud3d::~PointCloud3d()
{

}

void GEO::PointCloud3d::addPoint(Vec3D & p)
{
	_points.push_back(p);
	this->updateMaxMin(_points.size() - 1);
}

GEO::AABB GEO::PointCloud3d::getAABB()
{
	return AABB(_minPoint, _maxPoint);
}


GEO::Vec3D GEO::PointCloud3d::getPoint(int pos)
{
	if ((pos >= 0) && (pos < _points.size())) {
		return _points[pos];
	}
	return Vec3D();
}

GEO::PointCloud3d& GEO::PointCloud3d::operator=(const PointCloud3d & pointCloud)
{
	if (this != &pointCloud)
	{
		_points = pointCloud._points;
		_maxPoint = pointCloud._maxPoint;
		_minPoint = pointCloud._minPoint;
	}

	return *this;
}

void GEO::PointCloud3d::save(const std::string & filename)
{
	std::ofstream file(filename);

	for (int i = 0; i < _points.size(); ++i)
	{
		file << _points[i].getX() << ", " << _points[i].getY() << ", " << _points[i].getZ() << std::endl;
	}

	file.close();
}


/// PROTECTED METHODS

void GEO::PointCloud3d::updateMaxMin(int index)
{
	Vec3D point = _points[index];

	if (point.getX() < _minPoint.getX()) { _minPoint.setX(point.getX()); _minPointIndex.setX(index); }
	if (point.getY() < _minPoint.getY()) { _minPoint.setY(point.getY()); _minPointIndex.setY(index); }
	if (point.getZ() < _minPoint.getZ()) { _minPoint.setZ(point.getZ()); _minPointIndex.setZ(index); }

	if (point.getX() > _maxPoint.getX()) { _maxPoint.setX(point.getX()); _maxPointIndex.setX(index); }
	if (point.getY() > _maxPoint.getY()) { _maxPoint.setY(point.getY()); _maxPointIndex.setY(index); }
	if (point.getZ() > _maxPoint.getZ()) { _maxPoint.setZ(point.getZ()); _maxPointIndex.setZ(index); }
}


void GEO::PointCloud3d::getMostDistanced (int &a, int &b){
	//XXXX
	a=0; b=0;
}
