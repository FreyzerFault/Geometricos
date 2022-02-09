
/* 
 * File:   DrawSegment.h
 * Author: lidia
 *
 * Created on 19 de enero de 2021, 13:10
 */

#ifndef DRAWSEGMENT_H
#define DRAWSEGMENT_H


#include "Scene.h"
#include "SegmentLine.h"
#include "Draw.h"


class DrawSegment: public Draw {
    
    SegmentLine dt;
    
    public:
        
    DrawSegment (SegmentLine &t); 
    
    DrawSegment (const DrawSegment &ddt): dt (ddt.dt) , Draw() {}
    
    void drawIt ();
    void drawIt (TypeColor c);
    
    virtual ~DrawSegment(){};
};



#endif /* DRAWSEGMENT_H */

