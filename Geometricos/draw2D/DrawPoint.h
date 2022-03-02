/* 
 * File:   DrawPoint.h
 * Author: lidia
 *
 * Created on 14 de enero de 2021, 15:02
 */

#pragma once


#include "Point.h"
#include "Draw.h"


namespace GEO
{
	class DrawPoint: public Draw {
	    Point dp;
	public:
	    
	    DrawPoint(const Point &p);
	    DrawPoint (const DrawPoint &ddp): Draw() , dp (ddp.dp) {}
	    void drawIt ();
	    void drawIt (TypeColor c);
	    ~DrawPoint() override = default;
	};
}

