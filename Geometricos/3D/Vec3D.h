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
		bool collinear(Vec3D& a, Vec3D& b);

		// Distancia entre 2 puntos
		double distance(Vec3D& p);

		double module();

		Vec3D add(Vec3D& b);
		Vec3D sub(Vec3D& b);
		Vec3D scalarMul(double value);
		double dot(Vec3D& v);
		Vec3D cross(Vec3D& b);


		void set(unsigned int index, double value) { _value[index] = value; }
		void setVert(double x, double y, double z);
		void setY(double y);
		void setX(double x);
		void setZ(double z);
		
		// Devuelve las coordenadas en un vector<double>
		std::vector<double> getVector();

		double get(unsigned int index) const { return _value[index]; }		
		double getX();
		double getY();
		double getZ();
		
		
		Vec3D& operator=(const Vec3D& vector);


		bool operator==(const Vec3D& vector);
		bool operator!=(const Vec3D& vector);



		
		virtual void out();
	};
}

