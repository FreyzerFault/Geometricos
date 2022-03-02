
/* 
 * File:   DrawPlane.h
 * Author: lidia
 *
 * Created on 28 de enero de 2021, 17:11
 */
#pragma once

#include "Scene.h"
#include "Plane.h"
#include "Draw.h"

namespace GEO
{
    class DrawPlane : public Draw {

        Plane dt;

    public:

        DrawPlane(Plane& t);

        DrawPlane(const DrawPlane& ddt) : dt(ddt.dt), Draw() {}

        void drawIt();
        void drawIt(TypeColor c);

        virtual ~DrawPlane() {};
    };
}

