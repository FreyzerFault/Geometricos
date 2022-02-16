#pragma once
#include "Bezier.h"
#include "Draw.h"

namespace GEO
{
	class DrawBezier : public Draw
	{
		
	    Bezier dt;
	    
	public:
	        
	    DrawBezier (Bezier &bezier); 
	    
	    DrawBezier (const DrawBezier &ddt) : Draw() , dt (ddt.dt) {}
	    
	    void drawIt ();
	    void drawIt (TypeColor c);
	    
	};
}
