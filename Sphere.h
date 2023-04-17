#pragma once

#include <math.h>
#include "Vector.h"
#include "Ray.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere() : origin{}, radius{1.0} {}
	Sphere(Vector origin, double radius) : origin{origin}, radius{radius} {}

	virtual bool IsHitByRay(const Ray& ray, double tMin, double tMax, HitRecord& hit) const override;

public:
	Vector origin;
	double radius;
};

