#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/convex_hull_3.h>

#include "Triangle.h"
#include "TriangleModel.h"


namespace GEO
{
	class ConvexHull3D
	{
		
		typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
		typedef K::Point_3                                Point_3;
		typedef CGAL::Surface_mesh<Point_3>               Surface_mesh;
		typedef Surface_mesh::Face_iterator				  Face_iterator;
		typedef Surface_mesh::Face_index				  Face_index;
		typedef Surface_mesh::Face_range				  Face_range;
		typedef Surface_mesh::Vertex_iterator			  Vertex_iterator;

		Surface_mesh mesh;

		std::vector<Triangle3D> tris;

	public:

		ConvexHull3D() = default;
		ConvexHull3D(const std::string& path);
		ConvexHull3D(const PointCloud3D& pointCloud);
		ConvexHull3D(const TriangleModel& triangleModel);

		ConvexHull3D(const ConvexHull3D& orig) : mesh(orig.mesh), tris(orig.tris) {}
		
		void updateTris();

		const std::vector<Triangle3D>& getFaces() const { return tris; };
	};
}
