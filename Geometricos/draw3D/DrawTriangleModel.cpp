
/* 
 * File:   DrawTriangleModel.cpp
 * Author: lidia
 * 
 * Created on 21 de febrero de 2021, 11:35
 */

#include <glm/gtx/transform.hpp>
#include "DrawTriangleModel.h"


GEO::DrawTriangleModel::DrawTriangleModel (const TriangleModel &t):  dt (t), Draw(){  
   cleaning (); 
    
   for (int i=0; i< dt.vv.size(); i++){
    
    Vec3D aux = dt.vv[i]; 
    _vertices.push_back(glm::vec3 (aux.getX(), aux.getY(), aux.getZ()));
    
    Vec3D aux2 = dt.vn[i];
    _normals.push_back (glm::vec3 ( aux2.getX(), aux2.getY(), aux2.getZ() ) );
 
   }
   
   for (int i=0; i< dt.vi.size(); i++){
      
       unsigned ind = dt.vi[i];
       _indices.push_back ( ind );
         
   }
 
buildVAO ();  
    
}
   

void GEO::DrawTriangleModel::drawIt (){
 
    setShaderProgram ( "algeom" );
            //.setAmbient ( glm::vec3 ( .1, .3, .7 ) )
            //    .setDiffuse ( glm::vec3 ( .1, .3, .7 ) )
            //    .setEspecular ( glm::vec3 ( 1, 1, 1 ) )
            //    .setExpBright ( 100 )
            //    .apply ( glm::rotate (glm::radians(-90.0f), glm::vec3 ( 1.0f, .0f, .0f )));
    setDrawMode(TypeDraw::WIREFRAME );
    Scene::getInstance ()->addModel ( this );
    

}

void GEO::DrawTriangleModel::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
    
}


void GEO::DrawTriangleModel::drawItPlain (){
    setShaderProgram ( "algeom" )
            .setAmbient ( glm::vec3 ( .1, .3, .7 ) )
                .setDiffuse ( glm::vec3 ( .1, .3, .7 ) )
                .setEspecular ( glm::vec3 ( 1, 1, 1 ) )
                .setExpBright ( 100 )
                .apply ( glm::rotate (glm::radians(-90.0f), glm::vec3 ( 1.0f, .0f, .0f )));
    setDrawMode(TypeDraw::PLAIN);
    Scene::getInstance ()->addModel ( this );
    
}
