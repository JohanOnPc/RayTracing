#include "Glass.h"

#include "../Utilities.h"

bool Glass::ScatterRay(const Ray& ray, const HitRecord& hit, Vector& attenuation, Ray& scattered) const
{
	attenuation = Vector(1.0, 1.0, 1.0);
	double refractionRatio = hit.isFrontFace ? (1.0 / refractionIndex) : refractionIndex;

	double cosθ = DotProduct(~ray.direction, hit.normal);
	double sinθ = sqrt(1.0 - cosθ * cosθ);
	Vector direction;

	if ((refractionRatio * sinθ > 1.0) || Reflactance(cosθ, refractionIndex) > Random()) {
		direction = Reflect(ray.direction, hit.normal);
	}
	else {
		direction = Refract(ray.direction, hit.normal, refractionRatio);
	}
	scattered = Ray(hit.point, direction);
	
	return true;
}
