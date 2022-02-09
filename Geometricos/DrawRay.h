
/* 
 * File:   DrawRay.h
 * Author: lidia
 *
 * Created on 19 de enero de 2021, 20:00
 */

#ifndef DRAWRAY_H
#define DRAWRAY_H


#include "Scene.h"
#include "RayLine.h"
#include "Draw.h"


class DrawRay: public Draw {
    
    RayLine dt;
    
    public:
        
    DrawRay (RayLine &t); 
    
    DrawRay (const DrawRay &ddt): dt (ddt.dt) , Draw() {}
    
    void drawIt ();
    void drawIt (TypeColor c);
    
    virtual ~DrawRay(){};
};



#endif /* DRAWRAY_H */

