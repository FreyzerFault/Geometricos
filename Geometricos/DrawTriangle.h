
/* 
 * File:   DrawTriangle.h
 * Author: lidia
 *
 * Created on 5 de enero de 2021, 14:11
 */

#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H

//#include "Scene.h"
#include "Triangle.h"
#include "Draw.h"


class DrawTriangle: public Draw {
    
    Triangle dt;
    
    public:
        
    DrawTriangle (Triangle &t); 
    
    DrawTriangle (const DrawTriangle &ddt): dt (ddt.dt) , Draw() {}
    
    void drawIt ();
    void drawIt (TypeColor c);
    
    virtual ~DrawTriangle(){};
};


#endif /* DRAWTRIANGLE_H */

