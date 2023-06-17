#pragma once

#include "Vector.h"
#include "Ray.h"

class Camera
{
public:
	Camera(const Vector& lookFrom, const Vector& lookAt, const Vector& up, double vFOV, double aspectRatio, double aperture, double focusDistance, double openTime = 0.0, double closingTime = 0.0);

	Camera(const Camera&) = default;
	Camera& operator= (const Camera&) = default;

	Ray GetRay(double u, double v) const;

private:
	Vector origin;
	Vector LowLeft;
	Vector horizontalVector;
	Vector verticalVector;
	Vector horizontalUnit, verticalUnit, w;
	double lensRadius;
	double openTime, closingTime;
};

