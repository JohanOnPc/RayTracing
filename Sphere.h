#pragma once

#include "Vector.h"
#include "Ray.h"
#include "Hittable.h"

class Sphere : 
	public Hittable
{
public:
	Sphere() : origin{}, radius{1.0}, Hittable(nullptr) {}
	Sphere(Vector origin, double radius, std::shared_ptr<Material> material) : 
		origin{origin}, radius{radius}, Hittable(material) {}

	virtual bool IsHitByRay(const Ray& ray, double tMin, double tMax, HitRecord& hit) const override;

public:
	Vector origin;
	double radius;
};

