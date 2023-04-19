#pragma once

#include "../Ray.h"
#include "../objects/Hittable.h"

class Material
{
public:
	virtual bool ScatterRay(const Ray& ray, const struct HitRecord& hit, Vector& attenuation, Ray& scattered) const = 0;
};

