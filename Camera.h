#pragma once

#include "Vector.h"
#include "Ray.h"

class Camera
{
public:
	Camera();
	Camera(double aspectRatio, double viewportHeight, double viewportWidth, double focalLength);

	Camera(const Camera&) = default;
	Camera& operator= (const Camera&) = default;

	Ray GetRay(double u, double v) const;

private:
	Vector Origin;
	Vector LowLeft;
	Vector HorizontalUnitVector;
	Vector VerticalUnitVector;
};

