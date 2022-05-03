#include "TDelaunay.h"

GEO::TDelaunay::TDelaunay(const std::string& path)
{
	std::ifstream in(path);
	std::istream_iterator<CGAL::Point> begin(in);
	std::istream_iterator<CGAL::Point> end;

	delaunay = std::make_shared<CGAL::Delaunay>(begin, end);

	std::cout << "Numero de vertices: " << delaunay->number_of_vertices() << std::endl;
}

GEO::TDelaunay::TDelaunay(const PointCloud2D& pointCloud)
{
	const std::vector<GEO::Point>& points = pointCloud.getPoints();
	std::vector<CGAL::Point> cgalPoints;
	cgalPoints.reserve(points.size());

	for (const auto & point : points)
	{
		cgalPoints.emplace_back(point.getX(), point.getY(), 0);
	}

	delaunay = std::make_unique<CGAL::Delaunay>(cgalPoints.begin(), cgalPoints.end());

	std::cout << "Numero de vertices: " << delaunay->number_of_vertices() << std::endl;
}

void GEO::TDelaunay::getFaces()
{
	 delaunay->finite_face_handles();
}
