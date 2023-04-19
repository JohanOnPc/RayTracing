#pragma once

#include "Vector.h"

class Ray
{
public:
	Ray() : origin{}, direction{} {}
	Ray(const Vector& origin, const Vector& direction) : origin{ origin }, direction{ direction.GetNormal()} {}
	
	Ray(const Ray& ray) : origin{ray.origin}, direction{ray.direction.GetNormal()} {}
	Ray& operator= (const Ray& ray) { origin = ray.origin; direction = ray.direction.GetNormal(); return *this; }

	Vector at(const double t) const;
public:
	Vector origin;
	Vector direction;
};

