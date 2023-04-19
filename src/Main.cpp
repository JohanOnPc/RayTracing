#include <iostream>
#include <fstream>
#include <format>
#include <filesystem>

#include "Vector.h"
#include "Camera.h"
#include "Ray.h"
#include "Image.h"
#include "objects/Sphere.h"
#include "Scene.h"
#include "objects/Hittable.h"
#include "Utilities.h"
#include "materials/Lambertian.h"
#include "materials/Metal.h"

constexpr auto WIDTH = 1600;
constexpr auto HEIGHT = 900;
constexpr auto samples = 16;
constexpr auto maxDepth = 40;

Vector RayColor(const Ray& ray, const Scene& scene, int depth) {
	if (depth <= 0) {
		return Vector();
	}

	HitRecord hit;
	if (scene.IsHitByRay(ray, 0.0000001, infinity, hit)) {

		Ray scatter;
		Vector attenuation;
		
		if (hit.material->ScatterRay(ray, hit, attenuation, scatter)) {
			return attenuation * RayColor(scatter, scene, depth - 1);
		}

		return Vector();
	}
	double t = 0.5 * ((ray.Direction).GetNormal().y + 1);
	return Vector(1.0, 1.0, 1.0) * (1.0 - t) + Vector(0.0, 0.0, 1.0) * t;
}

int main() {
	Image image(WIDTH, HEIGHT);
	Camera camera;
	Scene scene;

	auto lambertianCenter = std::make_shared<Lambertian>(Lambertian(Vector(0.7, 0.3, 0.3)));
	auto lambertianGround = std::make_shared<Lambertian>(Lambertian(Vector(0.8, 0.8, 0.0)));
	auto metalLeft = std::make_shared<Metal>(Metal(Vector(0.8, 0.8, 0.8), 0.3));
	auto metalRight = std::make_shared<Metal>(Metal(Vector(0.8, 0.6, 0.2), 1.0));

	auto sphere = std::make_shared<Sphere>(Sphere({ 0.0, 0.0, -1.0 }, 0.5, lambertianCenter));
	auto world = std::make_shared<Sphere>(Sphere({ 0.0, -100.5, -1.0 }, 100.0, lambertianGround));
	auto left = std::make_shared<Sphere>(Sphere({ -1.0, 0.0, -1.0 }, 0.5, metalLeft));
	auto right = std::make_shared<Sphere>(Sphere({ 1.0, 0.0, -1.0 }, 0.5, metalRight));

	scene.AddObject(sphere);
	scene.AddObject(world);
	scene.AddObject(left);
	scene.AddObject(right);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			Vector color;
			for (int i = 0; i < samples; i++) {
				double u = (double(x) + Random()) / (WIDTH - 1);
				double v = (double(y) + Random()) / (HEIGHT - 1);
				color += RayColor(camera.GetRay(u, v), scene, maxDepth);
			}
			double sampleFactor = 1.0 / samples;
			image.WritePixel(x, y, color * sampleFactor);
		}

		std::cout << std::format("Line {} of {}\n", y, HEIGHT);
	}

	std::filesystem::current_path(std::filesystem::path("images"));
	image.WriteImageTofile("simpleSphereWithFuzziness.ppm");

	return 0;
}