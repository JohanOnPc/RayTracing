#pragma once

#include "Vector.h"

class Ray
{
public:
	Ray() : origin{}, direction{}, time{0.0} {}
	Ray(const Vector& origin, const Vector& direction, double time) : origin{ origin }, direction{ direction.GetNormal() }, time{ time } {}
	
	Ray(const Ray& ray) : origin{ ray.origin }, direction{ ray.direction.GetNormal() }, time{ ray.time } {}
	Ray& operator= (const Ray& ray) { origin = ray.origin; direction = ray.direction.GetNormal(); return *this; }

	Vector at(const double t) const;
public:
	Vector origin;
	Vector direction;
	double time;
};

