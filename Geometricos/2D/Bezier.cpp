#include "Bezier.h"

#include <fstream>
#include <iostream>

GEO::Bezier::Bezier()
= default;

GEO::Bezier::Bezier(std::string& filename)
{
	static std::string folderName = "Bezier/";
	std::ifstream is(folderName + filename + ".txt");
	if (!is.good())
		std::cout << "Archivo " + folderName + filename + " no se pudo abrir para crear la Curva de Bezier" << std::endl;

	std::string line;
	std::getline(is, line);
	
	while (std::getline(is, line))
	{
		// Formato: x;y

		if (!std::isdigit(line[0]) && line.find(';'))
			std::cout << "Formato de archivo de Bezier erroneo (" + line + ")" << std::endl;

		const double x = std::stod(line.substr(0, line.find(';')));
		const double y = std::stod(line.substr(line.find(';') + 1));

		addPoint(x, y);
	}

	is.close();
	return;
}

void GEO::Bezier::addPoint(Point p)
{
	_points.emplace_back(p);
}

void GEO::Bezier::addPoint(double x, double y)
{
	_points.emplace_back(x,y);
}

void GEO::Bezier::save(const std::string& filename) const
{
	static std::string folderName = "Bezier/";
	std::ofstream os(folderName + filename + ".txt");
	if (!os.good())
		std::cout << "Archivo " + folderName + filename + " no se pudo abrir para guardar la curva de Bezier" << std::endl;

	for (const auto& point : _points)
	{
		os << std::to_string(point.getX()) + ';' + std::to_string(point.getY()) << std::endl;
	}

	os.close();
}

GEO::Point GEO::Bezier::getPoint(unsigned int i) const
{
	if (i >= 0 && i < _points.size())
		return _points[i];

	return {};
}
