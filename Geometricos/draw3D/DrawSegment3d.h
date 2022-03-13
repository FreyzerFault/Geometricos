#pragma once

#include "Segment3D.h"
#include "Draw.h"


namespace GEO
{
    class DrawSegment3d : public Draw {

        Segment3D dt;

    public:

        DrawSegment3d(const Segment3D& segment);

        DrawSegment3d(const DrawSegment3d& ddt) : Draw(), dt(ddt.dt) {}

        DrawSegment3d& operator= (const DrawSegment3d& ddt) { dt = ddt.dt; return *this; }

        void drawIt();
        void drawIt(TypeColor c);

        ~DrawSegment3d() override = default;
    };
}

