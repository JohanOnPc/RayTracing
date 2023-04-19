#pragma once

#include <memory>

#include "../Ray.h"
#include "../Vector.h"
#include "../materials/Material.h"

struct HitRecord
{
	Vector point;
	Vector normal;
	double t = 0.0;
	std::shared_ptr<class Material> material;
};

class Hittable
{
public:
	Hittable(std::shared_ptr<class Material> material) : material{material} {}
	virtual bool IsHitByRay(const Ray& ray, double tMin, double tMax, HitRecord& hit) const = 0;

public:
	std::shared_ptr<Material> material;
};