#pragma once

#include <vector>
#include "Scene.h"
#include "AABB.h"
#include "Draw.h"
#include "DrawSegment3D.h"

namespace GEO
{
	class DrawAABB : public Draw {

		AABB _aabb;
		std::vector<DrawSegment3D> dsegment;

	public:
		friend class AABB;

		DrawAABB(const AABB& aabb);

		DrawAABB(const DrawAABB& dt) : Draw(), _aabb(dt._aabb), dsegment(dt.dsegment) {}

		virtual void drawIt();
		void drawIt(TypeColor c);

		~DrawAABB() override = default;
	};
}

