#pragma once

#include "Ray.h"
#include "Vector.h"

struct HitRecord
{
	Vector point;
	Vector normal;
	double t;
};

class Hittable
{
public:
	virtual bool IsHitByRay(const Ray& ray, double tMin, double tMax, HitRecord& hit) const = 0;
};