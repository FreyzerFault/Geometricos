#pragma once
#include "Bezier.h"
#include "Draw.h"

namespace GEO
{
	class DrawBezier : public Draw
	{
		
	    const Bezier* _bezier;
	    
	public:
	        
	    DrawBezier (const Bezier &bezier); 
	    
	    DrawBezier (const DrawBezier &drawBezier) : Draw() , _bezier(drawBezier._bezier) {}
	    
	    void drawIt ();
	    void drawIt (TypeColor c);
	    
	};
}
