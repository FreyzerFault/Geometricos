#pragma once
#include "Draw.h"
#include "VoxelGrid.h"


namespace GEO
{
	class DrawVoxelGrid : public Draw
	{
		VoxelGrid grid;
	public:

		DrawVoxelGrid(const VoxelGrid& grid);
		DrawVoxelGrid(const DrawVoxelGrid& dvg) : Draw(), grid(dvg.grid) {}

		void drawIt();
		void drawIt(TypeColor color);
		~DrawVoxelGrid() override = default;
	};
}
