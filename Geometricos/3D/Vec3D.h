#pragma once

#include <climits>
#include <vector>


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


		void set(unsigned int index, double value) { _value[index] = value; }
		void setVert(double x, double y, double z);
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

		
		virtual void out();
	};
}

