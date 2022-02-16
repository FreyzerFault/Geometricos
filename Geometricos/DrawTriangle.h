
/* 
 * File:   DrawTriangle.h
 * Author: lidia
 *
 * Created on 5 de enero de 2021, 14:11
 */

#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H

//#include "Scene.h"
#include "Triangle.h"
#include "Draw.h"


namespace GEO
{
    class DrawTriangle : public Draw {

        Triangle _triangle;

    public:

        DrawTriangle(Triangle& triangle);

        DrawTriangle(const DrawTriangle& drawTriangle): Draw(), _triangle(drawTriangle._triangle) {}

        void drawIt();
        void drawIt(TypeColor c);

        virtual ~DrawTriangle() = default;
    };
}


#endif /* DRAWTRIANGLE_H */

