#include "Camera.h"

Camera::Camera()
{
	double aspectRatio = 16.0 / 9.0;
	double viewportHeight = 2.0;
	double viewportWidth = 2.0 * aspectRatio;
	double focalLength = 1.0;

	Origin = Vector();
	HorizontalUnitVector = Vector(viewportWidth, 0.0);
	VerticalUnitVector = Vector(0.0, viewportHeight);
	LowLeft = Origin - HorizontalUnitVector * .5 - VerticalUnitVector * .5 - Vector(0.0, 0.0, focalLength);
}

Camera::Camera(double aspectRatio, double viewportHeight, double viewportWidth, double focalLength) :
	Origin{}, 
	HorizontalUnitVector{Vector(viewportWidth, 0.0)},
	VerticalUnitVector(Vector(0.0, viewportHeight)),
	LowLeft{Origin - HorizontalUnitVector * .5 - VerticalUnitVector * .5 - Vector(0.0, 0.0, focalLength)} {}

Ray Camera::GetRay(double u, double v) const
{
	return Ray(Origin, LowLeft + HorizontalUnitVector * u + VerticalUnitVector * v);
}
