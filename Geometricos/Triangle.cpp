#include "Triangle.h"

GEO::Triangle::Triangle(Vec2D& aa, Vec2D& bb, Vec2D& cc): a(aa), b(bb), c(cc)
{
}

GEO::Triangle::Triangle(const Triangle& tt): a(tt.a), b(tt.b), c(tt.c)
{
}
