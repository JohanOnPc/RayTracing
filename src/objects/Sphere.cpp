#include "Sphere.h"

bool Sphere::IsHitByRay(const Ray& ray, double tMin, double tMax, HitRecord& hit) const
{
	const Vector displacement = ray.origin - origin;
	double a = DotProduct(ray.direction, ray.direction);
	double b = DotProduct(ray.direction, displacement);
	double c = DotProduct(displacement, displacement) - radius * radius;
	double discriminant = b * b - a * c;

	if (discriminant < 0.0)
		return false;
	
	double root = (-b - sqrt(discriminant)) / a ;
	if (root < tMin || root > tMax) {
		root = (-b + sqrt(discriminant)) / a;
		if (root < tMin || root > tMax) {
			return false;
		}
	}
	
	hit.t = root;
	hit.point = ray.at(root);
	hit.SetNormal(ray, (hit.point - origin) / radius);
	hit.material = material;
	return true;
}
