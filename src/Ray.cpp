#include "Ray.h"

Vector Ray::at(const double t) const
{
    return origin + direction * t;
}
