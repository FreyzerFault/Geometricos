#pragma once

#include "Line3D.h"
#include "Draw.h"

namespace GEO
{
    class DrawLine3d : public Draw {

        Line3D dt;

    public:

        DrawLine3d(const Line3D& line);

        DrawLine3d(const DrawLine3d& ddt) : Draw(), dt(ddt.dt) {}

        void drawIt();
        void drawIt(TypeColor c);

        ~DrawLine3d() override = default;
    };
}

