
/* 
 * File:   DrawPoint.h
 * Author: lidia
 *
 * Created on 14 de enero de 2021, 15:02
 */

#ifndef DRAWPOINT_H
#define DRAWPOINT_H


#include "Scene.h"
#include "Point.h"
#include "Draw.h"

class DrawPoint: public Draw {
    Point dp;
public:
    
    DrawPoint(Point &p);
    DrawPoint (const DrawPoint &ddp): dp (ddp.dp) , Draw() {}
    void drawIt ();
    void drawIt (TypeColor c);
    virtual ~DrawPoint(){};

};

#endif /* DRAWPOINT_H */

