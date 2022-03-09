#pragma once

#include "Line3D.h"
#include "Draw.h"

namespace GEO
{
    class DrawLine3D : public Draw {

        Line3D dt;

    public:

        DrawLine3D(const Line3D& line);

        DrawLine3D(const DrawLine3D& ddt) : Draw(), dt(ddt.dt) {}

        void drawIt();
        void drawIt(TypeColor c);

        ~DrawLine3D() override = default;
    };
}

