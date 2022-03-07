
/* 
 * File:   DrawPolygonGeo.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 12:18
 */

#pragma once


#include "Polygon.h"
#include "Draw.h"


namespace GEO
{
    class DrawPolygon : public Draw {

        const Polygon* _polygon;

    public:

        DrawPolygon(const Polygon& polygon);

        DrawPolygon(const DrawPolygon& drawPolygon): Draw(), _polygon(drawPolygon._polygon) {}

        void drawIt();
        void drawIt(TypeColor c);

        ~DrawPolygon() override = default;
    };

}

