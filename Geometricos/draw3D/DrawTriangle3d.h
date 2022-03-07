#pragma once

#include "Scene.h"
#include "Triangle3D.h"
#include "Draw.h"


namespace GEO
{
    class DrawTriangle3D : public Draw {

        Triangle3D dt;

    public:

        DrawTriangle3D(const Triangle3D& triangle);

        DrawTriangle3D(const DrawTriangle3D& ddt) : Draw(), dt(ddt.dt) {}

        void drawIt();
        void drawIt(TypeColor c);

        ~DrawTriangle3D() override = default;;
    };

}

