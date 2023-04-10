#include <iostream>
#include <fstream>

#include "Vector.h"
#include "Camera.h"
#include "Ray.h"
#include "Image.h"
#include "Sphere.h"

#define WIDTH 1600
#define HEIGHT 900

Sphere circle(Vector(0.0, 0.0, -1.0), 0.5);
Sphere circle2(Vector(1.5, 0.0, -2.0), 1.4);

Vector RayColor(const Ray& ray) {
	double t = circle.IsHitByRay(ray);
	if (t > 0.0) {
		Vector unit = (ray.at(t) - circle.origin).Normalize();
		return (unit + Vector(1.0, 1.0, 1.0)) * 0.5;
	}
	t = 0.5 * ((ray.Direction).GetNormal().y + 1);
	return Vector(1.0, 1.0, 1.0) * (1.0 - t) + Vector(0.0, 0.0, 1.0) * t;
}

int main() {
	Image image(WIDTH, HEIGHT);
	Camera camera;
	
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			double u = double(x) / WIDTH;
			double v = double(y) / HEIGHT;
			image.WritePixel(x, y, RayColor(camera.GetRay(u, v)));
		}
	}

	image.WriteImageTofile("image.ppm");

	return 0;
}