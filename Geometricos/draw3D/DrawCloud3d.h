#pragma once

#include "Scene.h"
#include "PointCloud3D.h"
#include "Draw.h"


namespace GEO
{
    class DrawCloud3D : public Draw {

        PointCloud3D dt;

    public:


        DrawCloud3D(const PointCloud3D& t);

        DrawCloud3D(const DrawCloud3D& ddt) : Draw(), dt(ddt.dt) {}


        void drawIt();
        void drawIt(TypeColor c);

        ~DrawCloud3D() override = default;
    };
}

