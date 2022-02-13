
/* 
 * File:   DrawPolygonGeo.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 12:18
 */

#ifndef DRAWPolygon_H
#define DRAWPolygon_H

#include "Scene.h"
#include "Polygon.h"
#include "Draw.h"


namespace GEO
{
    class DrawPolygon : public Draw {

        Polygon dt;

    public:

        DrawPolygon(Polygon& t);

        DrawPolygon(const DrawPolygon& ddt) : dt(ddt.dt), Draw() {}

        void drawIt();
        void drawIt(TypeColor c);

        virtual ~DrawPolygon() {};
    };

}


#endif /* DRAWPolygonGeo_H */

