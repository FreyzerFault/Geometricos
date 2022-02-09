


namespace BasicGeometry
{
	constexpr double EPSILON = 0.00001;			// Avoids problems with the resolution.

	constexpr double CERO = 0.00000000;

	/**
	*	@brief Checks if two values are equal.
	*/
	bool equal(double a, double b);
	
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
		
};

inline bool BasicGeometry::equal(double a, double b) 
{
	return (abs(a - b) < EPSILON);
}

inline double BasicGeometry::determinant2x2(double a, double b, double c, double d)
{
	return (a * c - b * d);
}

inline double BasicGeometry::determinant3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i)
{
	return (a * e * i + g * b * f + c * d * h - c * e * g - i * d * b - a * h * f);
}

inline double BasicGeometry::min3(double a, double b, double c)
{
	return (a < b ? (a < c ? a : c) : (b < c ? b : c));
}

inline double BasicGeometry::max3(double a, double b, double c)
{
	return (a > b ? (a > c ? a : c) : (b > c ? b : c));
}

inline double BasicGeometry::min2(double a, double b)
{
	return (a < b ? a : b);
}

inline double BasicGeometry::max2(double a, double b)
{
	return (a > b ? a : b);
}