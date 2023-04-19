#pragma once

#include <limits>
#include <random>

#include "Vector.h"

constexpr auto pi = 3.14159265359;
constexpr auto infinity = std::numeric_limits<double>::infinity();

inline double Random(double min = 0.0, double max = 1.0)
{
	static std::uniform_real_distribution<double> distribution(min, max);
	static std::mt19937 generator;
	return distribution(generator);
}

inline Vector GetRandomVectorInHemisphere(const Vector& normal)
{
	Vector vec = Vector::GetRandomVectorInUnitSphere();
	if (DotProduct(vec, normal) > 0.0) {
		return vec;
	}
	else {
		return ~vec;
	}
}