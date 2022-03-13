#pragma once
#include <cfloat>
#include <cmath>

namespace GEO
{
	namespace BasicGeom
	{
		constexpr double EPSILON = DBL_EPSILON;			// Avoids problems with the resolution.

		constexpr double INFINITO = DBL_MAX;
		constexpr double menosINFINITO = DBL_MIN;

		constexpr double BIGNUM = 1000000;

		bool equal(double a, double b);
		bool lequal(double a, double b);
		bool gequal(double a, double b);
		
		double det2x2(double a, double b, double c, double d);
		double det3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i);
		
		double min3(double a, double b, double c);
		double max3(double a, double b, double c);

		double min2(double a, double b);
		double max2(double a, double b);

		// COMBINATORIA
		double combinatoria(double n, double k);


		inline bool equal(const double a, const double b)
		{
			return (abs(a - b) < EPSILON);
		}

		inline bool lequal(const double a, const double b)
		{
			return a < b || equal(a, b);
		}

		inline bool gequal(const double a, const double b)
		{
			return a > b || equal(a, b);
		}

		inline double det2x2(
			const double a, const double b,
			const double c, const double d)
		{
			return (a * c - b * d);
		}

		inline double det3x3(
			const double a, const double b, const double c,
			const double d, const double e, const double f,
			const double g, const double h, const double i)
		{
			return (a * e * i + g * b * f + c * d * h - c * e * g - i * d * b - a * h * f);
		}

		inline double min3(const double a, const double b, const double c)
		{
			return (a < b ? (a < c ? a : c) : (b < c ? b : c));
		}

		inline double max3(const double a, const double b, const double c)
		{
			return (a > b ? (a > c ? a : c) : (b > c ? b : c));
		}

		inline double min2(const double a, const double b)
		{
			return (a < b ? a : b);
		}

		inline double max2(const double a, const double b)
		{
			return (a > b ? a : b);
		}

		inline double combinatoria(const double n, const double k)
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