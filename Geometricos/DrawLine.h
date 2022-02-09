
/* 
 * File:   DrawLine.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 12:06
 */

#ifndef DRAWLINE_H
#define DRAWLINE_H


#include "Scene.h"
#include "Line.h"
#include "Draw.h"

class DrawLine: public Draw {
    
    Line dt;
    
    public:
        
    DrawLine (Line &t); 
    
    DrawLine (const DrawLine &ddt): dt (ddt.dt) , Draw() {}
    
    void drawIt ();
    void drawIt (TypeColor c);
    
    virtual ~DrawLine(){};
};



#endif /* DRAWLINE_H */

