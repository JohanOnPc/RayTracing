#include <iostream>
#include <fstream>

#include "Vector.h"
#include "Camera.h"
#include "Ray.h"
#include "Image.h"
#include "Sphere.h"
#include "Scene.h"
#include "Hittable.h"
#include "Utilities.h"

constexpr auto WIDTH = 1600;
constexpr auto HEIGHT = 900;
constexpr auto samples = 16;

Sphere circle(Vector(0.0, 0.0, -1.0), 0.5);
Sphere circle2(Vector(1.5, 0.0, -2.0), 1.4);

Vector RayColor(const Ray& ray, const Scene& scene) {
	HitRecord hit;
	if (scene.IsHitByRay(ray, 0, infinity, hit)) {
		return (hit.normal + Vector(1.0, 1.0, 1.0)) * 0.5;
	}
	double t = 0.5 * ((ray.Direction).GetNormal().y + 1);
	return Vector(1.0, 1.0, 1.0) * (1.0 - t) + Vector(0.0, 0.0, 1.0) * t;
}

int main() {
	Image image(WIDTH, HEIGHT);
	Camera camera;
	Scene scene;
	auto sphere = std::make_shared<Sphere>(Sphere({ 0.0, 0.0, -1.0 }, .5));
	auto world = std::make_shared<Sphere>(Sphere({ 0.0, -100.5, -1.0 }, 100.0));

	scene.AddObject(sphere);
	scene.AddObject(world);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			Vector color;
			for (int i = 0; i < samples; i++) {
				double u = (double(x) + random()) / (WIDTH - 1);
				double v = (double(y) + random()) / (HEIGHT - 1);
				color += RayColor(camera.GetRay(u, v), scene);
			}
			double sampleFactor = 1.0 / samples;
			image.WritePixel(x, y, color * sampleFactor);
		}
	}

	image.WriteImageTofile("simpleSphereWithSampling.ppm");

	return 0;
}