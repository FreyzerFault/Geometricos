#pragma once

#include "Segment3D.h"
#include "Draw.h"


namespace GEO
{
    class DrawSegment3D : public Draw {

        Segment3D dt;

    public:

        DrawSegment3D(const Segment3D& segment);

        DrawSegment3D(const DrawSegment3D& ddt) : Draw(), dt(ddt.dt) {}

        DrawSegment3D& operator= (const DrawSegment3D& ddt) { dt = ddt.dt; return *this; }

        void drawIt();
        void drawIt(TypeColor c);

        ~DrawSegment3D() override = default;
    };
}

