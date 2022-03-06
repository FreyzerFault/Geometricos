#pragma once

#include "Ray3D.h"
#include "Draw.h"


namespace GEO
{
    class DrawRay3d : public Draw {

        Ray3D dt;

    public:

        DrawRay3d(const Ray3D& ray);

        DrawRay3d(DrawRay3d& ddt) : Draw(), dt(ddt.dt) {}

        void drawIt();
        void drawIt(TypeColor c);

        ~DrawRay3d() override = default;
    };
}

