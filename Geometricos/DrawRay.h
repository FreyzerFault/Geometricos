/* 
 * File:   DrawRay.h
 * Author: lidia
 *
 * Created on 19 de enero de 2021, 20:00
 */

#pragma once

#include "RayLine.h"
#include "Draw.h"


namespace GEO
{
    class DrawRay : public Draw {

        RayLine* ray;

    public:

        DrawRay(RayLine& t);

        DrawRay(const DrawRay& ddt): Draw(), ray(ddt.ray) {}

        void drawIt();
        void drawIt(TypeColor c);

        ~DrawRay() override = default;
    };

}

