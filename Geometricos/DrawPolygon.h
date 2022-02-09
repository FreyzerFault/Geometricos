
/* 
 * File:   DrawPolygonGeo.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 12:18
 */

#ifndef DRAWPolygon_H
#define DRAWPolygon_H

#include "Scene.h"
#include "PolygonGeo.h"
#include "Draw.h"


class DrawPolygon : public Draw {
    
    PolygonGeo dt;
    
    public:
        
    DrawPolygon(PolygonGeo &t);
    
    DrawPolygon(const DrawPolygon&ddt): dt (ddt.dt) , Draw() {}
    
    void drawIt ();
    void drawIt (TypeColor c);
    
    virtual ~DrawPolygon(){};
};



#endif /* DRAWPolygonGeo_H */

