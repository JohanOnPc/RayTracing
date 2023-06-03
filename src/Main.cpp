#include <iostream>
#include <fstream>
#include <format>
#include <filesystem>
#include <chrono>

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
#include "materials/Glass.h"

constexpr auto WIDTH = 1920;
constexpr auto HEIGHT = 1080;
constexpr auto samples = 25;
constexpr auto maxDepth = 20;
constexpr double aspectRatio = (double)WIDTH / HEIGHT;

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
	double t = 0.5 * ((ray.direction).GetNormal().y + 1);
	return Vector(1.0, 1.0, 1.0) * (1.0 - t) + Vector(0.0, 0.0, 1.0) * t;
}

int main() {
	Image image(WIDTH, HEIGHT);
	Vector lookFrom = { 7, 7, 2 };
	Vector lookAt = { 0, 0, -1 };
	double focusDistance = (lookAt - lookFrom).Length();
	Camera camera(lookFrom, lookAt, { 0, 1, 0 }, 10.0, aspectRatio, 0.2, focusDistance);
	Scene scene;

	auto lambertianCenter =	std::make_shared<Lambertian>(Lambertian(Vector(0.1, 0.2, 0.5)));
	auto lambertianGround = std::make_shared<Lambertian>(Lambertian(Vector(0.8, 0.8, 0.0)));
	auto metalLeft =		std::make_shared<Metal>(Metal(Vector(0.8, 0.2, 0.6), 0.7));
	auto metalRight =		std::make_shared<Metal>(Metal(Vector(0.8, 0.6, 0.2), 0.2));
	auto glass =			std::make_shared<Glass>(Glass(1.5));

	auto sphere =		std::make_shared<Sphere>(Sphere({ 0.0, 0.0, -1.0 }, 0.5, lambertianCenter));
	auto world =		std::make_shared<Sphere>(Sphere({ 0.0, -100.5, -1.0 }, 100.0, lambertianGround));
	auto left =			std::make_shared<Sphere>(Sphere({ -1.0, 0.0, -1.0 }, 0.5, glass));
	auto insidLeft =	std::make_shared<Sphere>(Sphere({ -1.0, 0.0, -1.0 }, -0.47, glass));
	auto insideSphere = std::make_shared<Sphere>(Sphere({ -1.0, 0.0, -1.0 }, 0.2, glass));
	auto right =		std::make_shared<Sphere>(Sphere({ 1.0, 0.0, -1.0 }, 0.5, metalRight));
	auto backSphere =	std::make_shared<Sphere>(Sphere({ -7.0, 2.5, -5.0 }, 2.2, metalLeft));

	scene.AddObject(sphere);
	scene.AddObject(world);
	scene.AddObject(left);
	scene.AddObject(insidLeft);
	scene.AddObject(insideSphere);
	scene.AddObject(right);
	scene.AddObject(backSphere);

	auto t1 = std::chrono::high_resolution_clock::now();
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

		std::cout << std::format("Line {} of {}\n", y + 1, HEIGHT);
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = t2 - t1;
	std::cout << std::format("[INFO] Render took {:.5f} seconds\n", diff.count());

	std::filesystem::current_path(std::filesystem::path("images"));
	image.WriteImageTofile("simpleSphere.ppm");

	return 0;
}