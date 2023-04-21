#pragma once

#include <limits>
#include <random>

#include "Vector.h"

constexpr auto pi = 3.14159265359;
constexpr auto infinity = std::numeric_limits<double>::infinity();

inline double DegreesToRadians(const double degrees)
{
	return degrees * pi / 180.0;
}

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

inline Vector Reflect(const Vector& ray, const Vector& normal)
{
	return ray - 2.0 * DotProduct(ray, normal) * normal;
}

inline Vector Refract(const Vector& ray, const Vector& normal, const double refractionRatio)
{
	double cosθ = DotProduct(~ray, normal);
	Vector rayPerp = (ray + cosθ * normal) * refractionRatio;
	Vector rayParallel = -sqrt(fabs(1.0 - rayPerp.LengthSquared())) * normal;
	return rayPerp + rayParallel;
}

inline double Reflactance(const double cosθ, const double refractionIndex)
{
	double R0 = (1.0 - refractionIndex) / (1.0 + refractionIndex);
	R0 *= R0;
	return R0 + (1.0 - R0) * pow(1.0 - cosθ, 5);
}