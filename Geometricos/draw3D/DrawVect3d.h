/* 
 * File:   DrawVect3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 14:45
 */
#pragma once

#include "Scene.h"
#include "Vec3D.h"
#include "Draw.h"

namespace GEO
{
    class DrawVect3d : public Draw {
        Vec3D dp;
    public:

        DrawVect3d(Vec3D& p);
        DrawVect3d(DrawVect3d& ddp) : dp(ddp.dp), Draw() {}
        void drawIt();
        void drawIt(TypeColor c);
        virtual ~DrawVect3d() {};

    };
}

