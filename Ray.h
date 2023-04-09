#pragma once

#include "Vector.h"

class Ray
{
public:
	Ray() : Origin{}, Direction{} {}
	Ray(const Vector& Origin, const Vector& Direction) : Origin{ Origin }, Direction{ Direction } {}
	
	Ray(const Ray&) = default;
	Ray& operator= (const Ray&) = default;

	Vector at(const double t) const;
public:
	Vector Origin;
	Vector Direction;
};

