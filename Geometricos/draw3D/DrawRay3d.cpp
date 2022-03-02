
#include "Vec3D.h"
#include "DrawRay3d.h"


GEO::DrawRay3d::DrawRay3d (Ray3d &t): dt (t), Draw(){
    
    
    //XXXX
    

    buildVAO ();
    
}


void GEO::DrawRay3d::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawRay3d::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::LINE );
    Scene::getInstance ()->addModel ( this );
}


