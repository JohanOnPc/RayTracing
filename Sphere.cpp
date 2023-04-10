#include "Sphere.h"

double Sphere::IsHitByRay(const Ray& ray) const
{
    const Vector displacement = ray.Origin - origin;
    double a = DotProduct(ray.Direction, ray.Direction);
    double b = 2.0 * DotProduct(ray.Direction, displacement);
    double c = DotProduct(displacement, displacement) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0.0)
        return -1.0;
    else
        return (-b - sqrt(discriminant)) / (2 * a);
}
