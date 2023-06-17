#include "Metal.h"

#include "../Utilities.h"

bool Metal::ScatterRay(const Ray& ray, const HitRecord& hit, Vector& attenuation, Ray& scattered) const
{
    Vector reflected = Reflect(ray.direction, hit.normal);
    scattered = Ray(hit.point, reflected + Vector::GetRandomVectorInUnitSphere() * fuzziness, ray.time);
    attenuation = albedo;
    return DotProduct(scattered.direction, hit.normal) > 0.0;
}