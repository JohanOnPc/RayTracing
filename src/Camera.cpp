#include "Camera.h"

#include "Utilities.h"

Camera::Camera(const Vector& lookFrom, const Vector& lookAt, const Vector& up, double vFOV, double aspectRatio)
{
	double theta = DegreesToRadians(vFOV);
	double height = tan(theta / 2.0);
	double viewportHeight = 2.0 * height;
	double viewportWidth = viewportHeight * aspectRatio;

	w = (lookFrom - lookAt).Normalize();
	horizontalUnit = Vector::CrossProduct3D(up, w).Normalize();
	verticalUnit = Vector::CrossProduct3D(w, horizontalUnit);

	origin = lookFrom;
	horizontalVector = horizontalUnit * viewportWidth;
	verticalVector = verticalUnit * viewportHeight;
	LowLeft = origin - horizontalVector * .5 - verticalVector * .5 - w;
}

Ray Camera::GetRay(double u, double v) const
{
	return Ray(origin, LowLeft + horizontalVector * u + verticalVector * v - origin);
}
