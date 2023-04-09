#pragma once

#include <math.h>
#include "Vector.h"
#include "Ray.h"

class Sphere 
{
public:
	Sphere() : Origin{}, Radius{1.0} {}
	Sphere(Vector Origin, double Radius) : Origin{Origin}, Radius{Radius} {}

	bool IsHitByRay(const Ray& ray) const;

public:
	Vector Origin;
	double Radius;
};

