/* 
 * File:   DrawTriangle3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 17:28
 */
#pragma once

#include "Scene.h"
#include "Triangle3D.h"
#include "Draw.h"


namespace GEO
{
    class DrawTriangle3d : public Draw {

        Triangle3D dt;

    public:

        DrawTriangle3d(Triangle3D& t);

        DrawTriangle3d(DrawTriangle3d& ddt) : dt(ddt.dt), Draw() {}

        void drawIt();
        void drawIt(TypeColor c);

        virtual ~DrawTriangle3d() {};
    };

}

