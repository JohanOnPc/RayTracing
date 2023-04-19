#include "Camera.h"

Camera::Camera()
{
	double aspectRatio = 16.0 / 9.0;
	double viewportHeight = 2.0;
	double viewportWidth = 2.0 * aspectRatio;
	double focalLength = 1.0;

	origin = Vector();
	HorizontalUnitVector = Vector(viewportWidth, 0.0);
	VerticalUnitVector = Vector(0.0, viewportHeight);
	LowLeft = origin - HorizontalUnitVector * .5 - VerticalUnitVector * .5 - Vector(0.0, 0.0, focalLength);
}

Camera::Camera(double aspectRatio, double viewportHeight, double viewportWidth, double focalLength) :
	origin{}, 
	HorizontalUnitVector{Vector(viewportWidth, 0.0)},
	VerticalUnitVector(Vector(0.0, viewportHeight)),
	LowLeft{origin - HorizontalUnitVector * .5 - VerticalUnitVector * .5 - Vector(0.0, 0.0, focalLength)} {}

Ray Camera::GetRay(double u, double v) const
{
	return Ray(origin, LowLeft + HorizontalUnitVector * u + VerticalUnitVector * v);
}
