#pragma once
#include <string>
#include <fstream>
#include <memory>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

#include "PointCloud2D.h"

namespace CGAL
{
	// Kernel, traits for Delaunay
	typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
	typedef CGAL::Projection_traits_xy_3<K> Gt;
	typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;

	// Triangulation Faces
	typedef CGAL::Triangulation_vertex_base_2<K> Vb;
	typedef CGAL::Triangulation_face_base_with_info_2<CGAL::IO::Color, K> Fb;
	typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
	typedef CGAL::Triangulation_2<K, Tds> Triangulation;

	typedef K::Point_3 Point;

	typedef Triangulation::Face_handle Face_handle;
	typedef Triangulation::Point  TriPoint;
}

namespace GEO
{
	class TDelaunay
	{
		// Uso smart pointer para inicializarlo de forma tardia
		std::shared_ptr<CGAL::Delaunay> delaunay;

	public:
		TDelaunay() = default;
		TDelaunay(const std::string& path);
		TDelaunay(const PointCloud2D& pointCloud);

		TDelaunay(const TDelaunay& orig) : delaunay(orig.delaunay) {}

		void getFaces();
	};
}
