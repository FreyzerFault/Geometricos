#include "Triangle.h"

Triangle::Triangle(Vect2d& aa, Vect2d& bb, Vect2d& cc): a(aa), b(bb), c(cc)
{
}

Triangle::Triangle(const Triangle& tt): a(tt.a), b(tt.b), c(tt.c)
{
}
