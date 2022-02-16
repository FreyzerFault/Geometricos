#pragma once
#include <cfloat>
#include <cmath>

namespace GEO
{
	namespace BasicGeom
	{
		constexpr double EPSILON = 0.00001;			// Avoids problems with the resolution.

		constexpr double CERO = 0.00000000;

		constexpr double INFINITO = DBL_MAX;
		constexpr double menosINFINITO = DBL_MIN;

		/**
		*	@brief Checks if two values are equal.
		*/
		bool equal(double a, double b);
		bool lequal(double a, double b);
		bool gequal(double a, double b);

		/**
		*	@brief Determinant 2x2.
		*/
		double determinant2x2(double a, double b, double c, double d);

		/**
		*	@brief Determinant 3x3.
		*/
		double determinant3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i);

		/**
		*	@brief Returns the mininum value from the 3 specified values.
		*/
		double min3(double a, double b, double c);

		/**
		*	@brief Returns the maximum value from the 3 specified values.
		*/
		double max3(double a, double b, double c);

		/**
	*	@brief Returns the mininum value from the 2 specified values.
	*/
		double min2(double a, double b);

		/**
		*	@brief Returns the maximum value from the 3 specified values.
		*/
		double max2(double a, double b);

		// COMBINATORIA
		double combinatoria(double n, double k);


		inline bool BasicGeom::equal(double a, double b)
		{
			return (abs(a - b) < EPSILON);
		}

		inline bool BasicGeom::lequal(double a, double b)
		{
			return a < b || equal(a, b);
		}

		inline bool BasicGeom::gequal(double a, double b)
		{
			return a > b || equal(a, b);
		}

		inline double BasicGeom::determinant2x2(double a, double b, double c, double d)
		{
			return (a * c - b * d);
		}

		inline double BasicGeom::determinant3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i)
		{
			return (a * e * i + g * b * f + c * d * h - c * e * g - i * d * b - a * h * f);
		}

		inline double BasicGeom::min3(double a, double b, double c)
		{
			return (a < b ? (a < c ? a : c) : (b < c ? b : c));
		}

		inline double BasicGeom::max3(double a, double b, double c)
		{
			return (a > b ? (a > c ? a : c) : (b > c ? b : c));
		}

		inline double BasicGeom::min2(double a, double b)
		{
			return (a < b ? a : b);
		}

		inline double BasicGeom::max2(double a, double b)
		{
			return (a > b ? a : b);
		}

		inline double combinatoria(double n, double k)
		{
			if (equal(k,0))
				return 1;

			if (equal(k,1))
				return n;

			// Combinatoria = n(n-1)(n-2)...(n - k+1) / k!
			double comb = n;
			for (int i = 1; i < k ; ++i)
				comb *= n - i;

			// Factorial de k = 1*2*3*4*...*k
			double factorial = 1;
			for (int i = 1; i <= k; ++i)
				factorial *= i;

			return comb / factorial;
		}
	}
}