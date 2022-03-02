
/* 
 * File:   DrawPointCloud.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 13:29
 */

#ifndef DRAWPOINTCLOUD_H
#define DRAWPOINTCLOUD_H

#include "Scene.h"
#include "PointCloud.h"
#include "Draw.h"


namespace GEO
{
	class DrawPointCloud: public Draw {
	    
	    PointCloud dt;
	    
	    public:
	        
	    DrawPointCloud (const PointCloud &t); 
	    
	    DrawPointCloud (const DrawPointCloud &ddt): dt (ddt.dt) , Draw() {}
	    
	    void drawIt ();
	    void drawIt (TypeColor c);

	    ~DrawPointCloud() override = default;
	};
}



#endif /* DRAWPOINTCLOUD_H */

