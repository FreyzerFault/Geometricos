#pragma once

#include "Scene.h"
#include "Draw.h"
#include "TriangleModel.h"

namespace GEO
{
	class DrawTriangleModel : public Draw {

		TriangleModel dt;

	public:
		DrawTriangleModel(const TriangleModel& triModel);

		DrawTriangleModel(const DrawTriangleModel& ddt) : Draw(), dt(ddt.dt) {}


		void drawItPlain();
		void drawIt();
		void drawIt(TypeColor c);

		~DrawTriangleModel() override = default;;
	};
}

