
/* 
 * File:   DrawPointCloud.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 13:29
 */

#ifndef DRAWPOINTCLOUD_H
#define DRAWPOINTCLOUD_H

#include "Scene.h"
#include "PointCloud2D.h"
#include "Draw.h"


namespace GEO
{
	class DrawCloud: public Draw {
	    
	    PointCloud2D dt;
	    
	    public:
	        
	    DrawCloud (const PointCloud2D &t); 
	    
	    DrawCloud (const DrawCloud &ddt): dt (ddt.dt) , Draw() {}
	    
	    void drawIt ();
	    void drawIt (TypeColor c);

	    ~DrawCloud() override = default;
	};
}



#endif /* DRAWPOINTCLOUD_H */

