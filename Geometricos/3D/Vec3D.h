#pragma once

#include <climits>
#include <vector>
#include <sstream>

#include "BasicGeom.h"

#include "pcl/point_types.h"


namespace GEO
{
	class Triangle3D;
	
	class Vec3D
	{
	protected:
		constexpr static int DEFAULT_VALUE = INT_MAX;	// Value of X and Y coordinates for an incomplete vector.

		enum Axes { X, Y, Z };

	private:
		double _value[3];

	public:
		Vec3D(); // Con DEFAULT_VALUE
		
		Vec3D(double x, double y, double z);

		// Coordenadas polares a partir de un punto central p
		Vec3D(const Vec3D& p, double r, double theta, double phi);
		
		Vec3D(const Vec3D& vector);
		
		virtual ~Vec3D() = default;
		

		// Es colinear a la recta formada por a,b
		bool collinear(const Vec3D& a, const Vec3D& b) const;

		// Distancia entre 2 puntos
		double distance(const Vec3D& p) const;

		double module() const;

		Vec3D normalize() const;

		Vec3D add(const Vec3D& b) const;
		Vec3D sub(const Vec3D& b) const;
		Vec3D scalarMul(double value) const;
		double dot(const Vec3D& v) const;
		Vec3D cross(const Vec3D& b) const;

		// Valid point: ninguna coord tiene el valor DEFAULT_VALUE
		bool isValid() const { return BasicGeom::equal(getX(), DEFAULT_VALUE); }

		void set(unsigned int index, double value) { _value[index] = value; }
		void setVec(double x, double y, double z);
		void setY(double y);
		void setX(double x);
		void setZ(double z);
		
		// Devuelve las coordenadas en un vector<double>
		std::vector<double> getVector() const;

		double get(unsigned int index) const { return _value[index]; }		
		double getX() const;
		double getY() const;
		double getZ() const;
		
		
		Vec3D& operator=(const Vec3D& vector);


		bool operator==(const Vec3D& vector) const;
		bool operator!=(const Vec3D& vector) const;

		Vec3D operator+(const Vec3D& v) const;
		Vec3D operator-(const Vec3D& v) const;
		Vec3D operator*(double s) const;
		Vec3D operator/(double s) const;
		
		Vec3D operator+(const double a) const;
		Vec3D operator-(const double a) const;

		// Todas las coords son menores
		bool operator<(const Vec3D& p) const;
		bool operator>(const Vec3D& p) const;

		// Inverso
		Vec3D operator-() const { return {-_value[X], -_value[Y], -_value[Z]}; }

		virtual std::string toString() const;
		virtual void out() const;

		pcl::PointXYZ toPointXYZ() const { return {(float)getX(), (float)getY(), (float)getZ()}; }

		Vec3D ceil() const { return {std::ceil(getX()), std::ceil(getY()), std::ceil(getZ())}; }
	};
}

