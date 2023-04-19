#pragma once

#include "../objects/Hittable.h"

class Glass :
	public Material
{
public:
	Glass() : refractionIndex{1.0} {}
	Glass(double refractionIndex) : refractionIndex{refractionIndex} {}

	virtual bool ScatterRay(const Ray& ray, const struct HitRecord& hit, Vector& attenuation, Ray& scattered) const override;

public:
	double refractionIndex;
};