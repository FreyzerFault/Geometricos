
/* 
 * File:   Line3d.h
 * Author: lidia
 *
 * Created on 25 de enero de 2021, 19:55
 */
#pragma once

#include "Edge3D.h"
#include "Line3D.h"

namespace GEO
{

	class Line3D : public Edge3D
	{
	public:
		enum classifyLines { NON_INTERSECT, PARALLEL, INTERSECT, THESAME };

	private:
		// La linea es infinita, cualquier valor de t es valido
		bool isTvalid(double t) const override { return true; }

	public:
		Line3D(const Vec3D& orig, const Vec3D& dest);
		
		Line3D(const Line3D& line) = default;
		
		~Line3D() override = default;
		
		double distance(const Line3D& line) const;


		// Vector normal por un punto p
		Line3D normalLine(Vec3D& p) const;

		
		Line3D& operator=(const Line3D& line);

		void out() override;


	};
}

