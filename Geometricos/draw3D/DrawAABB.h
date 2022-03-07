#pragma once

#include <vector>
#include "Scene.h"
#include "AABB.h"
#include "Draw.h"
#include "DrawSegment3d.h"

namespace GEO
{
	class DrawAABB : public Draw {

		AABB _aabb;
		std::vector<DrawSegment3d> dsegment;

	public:
		friend class AABB;

		DrawAABB(const AABB& aabb);

		DrawAABB(const DrawAABB& dt) : Draw(), _aabb(dt._aabb), dsegment(dt.dsegment) {}

		void drawIt();
		void drawIt(TypeColor c);

		~DrawAABB() override = default;
	};
}

