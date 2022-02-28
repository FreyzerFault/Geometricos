/* 
 * File:   DrawTriangle.h
 * Author: lidia
 *
 * Created on 5 de enero de 2021, 14:11
 */
#pragma once

#include "Triangle.h"
#include "Draw.h"


namespace GEO
{
    class DrawTriangle : public Draw {

        Triangle _triangle;

    public:

        DrawTriangle(const Triangle& triangle);

        DrawTriangle(const DrawTriangle& drawTriangle): Draw(), _triangle(drawTriangle._triangle) {}

        void drawIt();
        void drawIt(TypeColor c);

        ~DrawTriangle() override = default;
    };
}

