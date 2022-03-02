
/* 
 * File:   DrawSegment3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 18:12
 */
#pragma once

#include "Scene.h"
#include "Segment3d.h"
#include "Draw.h"


namespace GEO
{
    class DrawSegment3d : public Draw {

        Segment3d dt;

    public:

        DrawSegment3d(Segment3d& t);

        DrawSegment3d(const DrawSegment3d& ddt) : dt(ddt.dt), Draw() {}

        DrawSegment3d& operator= (const DrawSegment3d& ddt) { dt = ddt.dt; return *this; }

        void drawIt();
        void drawIt(TypeColor c);

        virtual ~DrawSegment3d() {};
    };
}

