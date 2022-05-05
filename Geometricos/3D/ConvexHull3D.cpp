#include "ConvexHull3D.h"

GEO::ConvexHull3D::ConvexHull3D(const std::string& path)
{
	std::ifstream in( path );
	if (!in.good())
		throw std::exception(("El archivo " + path + " no se ha podido leer").c_str());

	std::vector<Point_3> points;
	Point_3 p;
	while(in >> p){
		points.push_back(p);
	}

	CGAL::convex_hull_3(points.begin(), points.end(), mesh);

	updateTris();
}

GEO::ConvexHull3D::ConvexHull3D(const PointCloud3D& pointCloud)
{
	std::vector<Point_3> points;
	for (const Vec3D& point : pointCloud.getPoints())
	{
		points.emplace_back(point.getX(), point.getY(), point.getZ());
	}

	CGAL::convex_hull_3(points.begin(), points.end(), mesh);

	std::cout << "Convex Hull calculado con " << mesh.num_vertices() << " vertices" << std::endl;

	updateTris();
}

GEO::ConvexHull3D::ConvexHull3D(const TriangleModel& triangleModel)
	: ConvexHull3D(triangleModel.getCloud())
{
}

void GEO::ConvexHull3D::updateTris()
{
	tris.reserve(mesh.number_of_faces());
	
	for (const Face_index face : mesh.faces())
	{
		Point_3 cgalPoints[3];
		int i = 0;
		for (const Surface_mesh::Vertex_index vertex : mesh.vertices_around_face(mesh.halfedge(face)))
		{
			if (i >= 3)
				std::cout << "Hay mas de 3 vertices en esta cara" << std::endl;
			else
				cgalPoints[i++] = mesh.point(vertex);
		}
		Vec3D points[3] = {
			{cgalPoints[0].x(), cgalPoints[0].y(), cgalPoints[0].z()},
			{cgalPoints[1].x(), cgalPoints[1].y(), cgalPoints[1].z()},
			{cgalPoints[2].x(), cgalPoints[2].y(), cgalPoints[2].z()}
		};
		tris.emplace_back(points[0], points[1], points[2]);
	}
}
