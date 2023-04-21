#pragma once

#include "Vector.h"
#include "Ray.h"

class Camera
{
public:
	Camera(const Vector& lookFrom, const Vector& lookAt, const Vector& up, double vFOV, double aspectRatio, double aperture, double focusDistance);

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
};

