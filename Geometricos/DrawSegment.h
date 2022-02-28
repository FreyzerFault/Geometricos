#pragma once

#include "SegmentLine.h"
#include "Draw.h"


namespace GEO
{
    class DrawSegment : public Draw {

        SegmentLine dt;

    public:

        DrawSegment(const SegmentLine& t);

        DrawSegment(const DrawSegment& ddt): Draw(), dt(ddt.dt) {}

        void drawIt();
        void drawIt(TypeColor c);

        ~DrawSegment() override = default;
    };

}

