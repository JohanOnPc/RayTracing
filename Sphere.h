#pragma once

#include <math.h>
#include "Vector.h"
#include "Ray.h"

class Sphere 
{
public:
	Sphere() : origin{}, radius{1.0} {}
	Sphere(Vector origin, double radius) : origin{origin}, radius{radius} {}

	double IsHitByRay(const Ray& ray) const;

public:
	Vector origin;
	double radius;
};

