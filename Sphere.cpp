#include "Sphere.h"

bool Sphere::IsHitByRay(const Ray& ray, double tMin, double tMax, HitRecord& hit) const
{
	const Vector displacement = ray.Origin - origin;
	double a = DotProduct(ray.Direction, ray.Direction);
	double b = DotProduct(ray.Direction, displacement);
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
	hit.normal = (hit.point - origin).GetNormal();
	return true;
}
