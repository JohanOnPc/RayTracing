#include "Camera.h"

#include "Utilities.h"

Camera::Camera(const Vector& lookFrom, const Vector& lookAt, const Vector& up, double vFOV, double aspectRatio, double aperture, double focusDistance, double openTime, double closingTime) :
	openTime{openTime}, closingTime{closingTime}
{
	double theta = DegreesToRadians(vFOV);
	double height = tan(theta / 2.0);
	double viewportHeight = 2.0 * height;
	double viewportWidth = viewportHeight * aspectRatio;

	w = (lookFrom - lookAt).Normalize();
	horizontalUnit = Vector::CrossProduct3D(up, w).Normalize();
	verticalUnit = Vector::CrossProduct3D(w, horizontalUnit);

	origin = lookFrom;
	horizontalVector = horizontalUnit * viewportWidth * focusDistance;
	verticalVector = verticalUnit * viewportHeight * focusDistance;
	LowLeft = origin - horizontalVector * 0.5 - verticalVector * 0.5 - w * focusDistance;

	lensRadius = aperture / 2.0;
}

Ray Camera::GetRay(double u, double v) const
{
	Vector offset = Vector::GetRandomVectorInUnitDisk() * lensRadius;
	offset = horizontalUnit * offset.x + verticalUnit * offset.y;
	return Ray(origin + offset, LowLeft + horizontalVector * u + verticalVector * v - origin - offset, Random(openTime, closingTime));
}
