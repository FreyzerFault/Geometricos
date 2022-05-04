#include "TDelaunay.h"

GEO::TDelaunay::TDelaunay(const std::string& path)
{
	std::ifstream in(path);
	std::istream_iterator<CGAL::Point> begin(in);
	std::istream_iterator<CGAL::Point> end;
	
	triangulation.insert(begin, end);

	updateTris();
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

	triangulation.insert(cgalPoints.begin(), cgalPoints.end());
	
	updateTris();
}

void GEO::TDelaunay::updateTris()
{
	tris.reserve(triangulation.number_of_faces());
	for (const CGAL::Face_handle fh : triangulation.finite_face_handles())
	{
		const CGAL::Vertex_handle vertexHandles[3] = {fh->vertex(0), fh->vertex(1), fh->vertex(2)};
		const CGAL::Point cgalPoints[3] = {vertexHandles[0]->point(), vertexHandles[1]->point(), vertexHandles[2]->point()};
		Point points[3] = {
			{cgalPoints[0].x(), cgalPoints[0].y()},
			{cgalPoints[1].x(), cgalPoints[1].y()},
			{cgalPoints[2].x(), cgalPoints[2].y()}
		};
		tris.emplace_back(points[0], points[1], points[2]);
	}
}

const std::vector<GEO::Triangle>& GEO::TDelaunay::getFaces() const
{
	return tris;
}
