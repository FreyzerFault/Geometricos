#pragma once
#include <string>
#include <fstream>
#include <memory>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

#include "PointCloud2D.h"
#include "Triangle.h"

namespace CGAL
{
	// Kernel, traits for Delaunay
	typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
	typedef CGAL::Projection_traits_xy_3<K> Gt;
	typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;
	typedef Delaunay::Edge_iterator Edge_iterator;
	typedef Delaunay::Point Point;
	typedef Delaunay::Face_handle Face_handle;
	typedef Delaunay::Vertex_handle Vertex_handle;
}

namespace GEO
{
	class TDelaunay
	{
		CGAL::Delaunay triangulation;

		std::vector<Triangle> tris;

	public:
		TDelaunay() = default;
		TDelaunay(const std::string& path);
		TDelaunay(const PointCloud2D& pointCloud);

		TDelaunay(const TDelaunay& orig) : triangulation(orig.triangulation) {}

		void updateTris();

		const std::vector<Triangle>& getFaces() const;
	};
}
