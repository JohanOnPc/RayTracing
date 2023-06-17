#include "Lambertian.h"

bool Lambertian::ScatterRay(const Ray& ray, const HitRecord& hit, Vector& attenuation, Ray& scattered) const
{
	Vector scatterDirection = hit.normal + Vector::GetRandomVectorInUnitSphere();

	if (scatterDirection.IsNearZero()) {
		scatterDirection = hit.normal;
	}

	scattered = Ray(hit.point, scatterDirection, ray.time);
	attenuation = albedo;
	return true;
}
