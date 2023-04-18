#pragma once

#include <limits>
#include <random>

constexpr auto pi = 3.14159265359;
constexpr auto infinity = std::numeric_limits<double>::infinity();

inline double random(double min = 0.0, double max = 1.0)
{
	static std::uniform_real_distribution<double> distribution(min, max);
	static std::mt19937 generator;
	return distribution(generator);
}