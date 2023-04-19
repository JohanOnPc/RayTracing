#include "Metal.h"

bool Metal::ScatterRay(const Ray& ray, const HitRecord& hit, Vector& attenuation, Ray& scattered) const
{
    Vector reflected = ray.Direction.GetNormal() - hit.normal * DotProduct(ray.Direction.GetNormal(), hit.normal) * 2.0;
    scattered = Ray(hit.point, reflected + Vector::GetRandomVectorInUnitSphere() * fuzziness);
    attenuation = albedo;
    return DotProduct(scattered.Direction, hit.normal) > 0.0;
}