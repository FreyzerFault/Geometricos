
/* 
 * File:   DrawCloud3d.h
 * Author: lidia
 *
 * Created on 28 de enero de 2021, 12:27
 */
#pragma once

#include "Scene.h"
#include "PointCloud3d.h"
#include "Draw.h"


namespace GEO
{
    class DrawCloud3d : public Draw {

        PointCloud3d dt;

    public:


        DrawCloud3d(PointCloud3d& t);

        DrawCloud3d(const DrawCloud3d& ddt) : dt(ddt.dt), Draw() {}


        void drawIt();
        void drawIt(TypeColor c);

        virtual ~DrawCloud3d() {};
    };
}

