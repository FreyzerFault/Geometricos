
/* 
 * File:   DrawLine.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 12:06
 */

#pragma once

#include "Line.h"
#include "Draw.h"

namespace GEO
{
	class DrawLine: public Draw {
	    
	    Line* _line;
	    
	    public:
	        
	    DrawLine (Line &line); 
	    
	    DrawLine (const DrawLine &drawLine) : Draw() , _line (drawLine._line) {}
	    
	    void drawIt ();
	    void drawIt (TypeColor c);

	    ~DrawLine() override = default;
	};
}

