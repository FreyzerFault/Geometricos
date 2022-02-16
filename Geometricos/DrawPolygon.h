
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

        Polygon* _polygon;

    public:

        DrawPolygon(Polygon& polygon);

        DrawPolygon(const DrawPolygon& drawPolygon): Draw(), _polygon(drawPolygon._polygon) {}

        void drawIt();
        void drawIt(TypeColor c);

        virtual ~DrawPolygon() = default;
    };

}


#endif /* DRAWPolygonGeo_H */

