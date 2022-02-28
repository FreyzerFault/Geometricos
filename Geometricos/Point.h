// ReSharper disable CppHiddenFunction
#pragma once

#include <climits>
#include <string>

#include "BasicGeom.h"

namespace GEO
{
	class Vec2D;

	/**
	*	@brief This class represents a 2D structure. This will be also the skeleton for other 2D structures such as Vertex or Vector.
	*	@author Lidia
	*/
	class Point
	{
	protected:
		constexpr static double DEFAULT_VALUE = INT_MAX; // Value of X and Y coordinates for an incomplete Point.

	public:
		enum class PointClassification
		{	LEFT,
			RIGHT,
			FORWARD,
			BACKWARD,
			BETWEEN,
			ORIGIN,
			DEST
		};

		// Para sacar por consola la posicion relativa
		static std::string classifyToString(PointClassification c);

	protected:
		double _x, _y;

	public:
		// Iniciado a DEFAULT_VALUE (INT_MAX)
		Point();

		// Constructor con Coordenadas POLARES si polar == true
		Point(double x, double y, bool polar = false);

		Point(const Vec2D& v);

		Point(const Point& point) = default;

		virtual ~Point() = default;

		// Clasifica la posicion del Punto respecto al Segmento p0,p1
		PointClassification classify(const Point& p0, const Point& p1) const;

		// CLASIFICACI�N
		bool forward(const Point& a, const Point& b) const { return classify(a, b) == PointClassification::FORWARD; }
		bool backward(const Point& a, const Point& b) const { return classify(a, b) == PointClassification::BACKWARD; }
		bool isBetween(const Point& a, const Point& b) const { return classify(a, b) == PointClassification::BETWEEN; }
		bool left(const Point& a, const Point& b) const { return classify(a, b) == PointClassification::LEFT; }
		bool right(const Point& a, const Point& b) const { return classify(a, b) == PointClassification::RIGHT; }
		bool leftAbove(const Point& a, const Point& b) const;
		bool rightAbove(const Point& a, const Point& b) const;

		// Colinear con a y b
		bool colinear(const Point& a, const Point& b) const;

		// Distancia entre Puntos
		double distPoint(const Point& p) const;

		bool distinct(const Point& p) const;
		bool equal(const Point& pt) const;		

		// �NGULO del punto como Coordenada POLAR
		double getAlpha() const;

		// M�DULO
		double getModule() const;
		
		// PENDIENTE de la recta this -> p
		double slope(const Point& p) const;

		// Area del Triangulo formado por [this,a,b] * 2 (Area del Cuadrado)
		double triangleArea2(const Point& a, const Point& b) const;

		Point& operator=(const Point& point) = default;
		
		// Vector entre 2 puntos
		Vec2D operator-(const Point& v) const;

		// Punto resultante de sumar o restar un vector
		Point operator+(const Vec2D& v) const;
		Point operator-(const Vec2D& v) const;

		virtual void out() const;
		std::string toString() const;
		
		
		double getX() const { return _x; }
		double getY() const { return _y; }
		
		void setX(const double x) { _x = x; }
		void setY(const double y) { _y = y; }

		void set(const double x, const double y)
		{
			this->_x = x;
			this->_y = y;
		}
		
		bool isValid() const { return BasicGeom::equal(_x, DEFAULT_VALUE) && BasicGeom::equal(_y, DEFAULT_VALUE); }

	};
}
