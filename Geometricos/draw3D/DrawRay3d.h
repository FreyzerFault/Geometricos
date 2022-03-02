
/* 
 * File:   DrawRay3d3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 17:50
 */
#pragma once

#include "Scene.h"
#include "Ray3d.h"
#include "Draw.h"


namespace GEO
{
    class DrawRay3d : public Draw {

        Ray3d dt;

    public:

        DrawRay3d(Ray3d& t);

        DrawRay3d(DrawRay3d& ddt) : dt(ddt.dt), Draw() {}

        void drawIt();
        void drawIt(TypeColor c);

        virtual ~DrawRay3d() {};
    };
}

