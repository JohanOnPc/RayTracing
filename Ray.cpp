#include "Ray.h"

Vector Ray::at(const double t) const
{
    return Origin + Direction * t;
}
