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
#include "ConcurrentRenderer.h"

constexpr auto WIDTH = 1920;
constexpr auto HEIGHT = 1080;
constexpr auto samples = 25;
constexpr auto maxDepth = 20;
constexpr double aspectRatio = (double)WIDTH / HEIGHT;

Scene CreateRandomScene()
{
	Scene scene;

	auto groundMaterial = std::make_shared<Lambertian>(Lambertian({ 0.5, 0.5, 0.5 }));
	scene.AddObject(std::make_shared<Sphere>(Vector(0, -1000, 0), 1000, groundMaterial));

	for (int i = -20; i < 11; i++) {
		for (int j = -20; j < 11; j++) {
			double chooseMaterial = Random();

			Vector center = { i + 0.9 * Random(), 0.2, j + 0.9 * Random() };

			if ((center - Vector(4, 0.2, 0)).Length() > 0.9) {
				std::shared_ptr<Material> material;

				if (chooseMaterial < 0.8) {
					Vector albedo = { Random() * Random(), Random() * Random(), Random() * Random() };
					material = std::make_shared<Lambertian>(Vector(albedo));
					scene.AddObject(std::make_shared<Sphere>(Sphere(center, 0.2, material)));
				}

				else if (chooseMaterial < 0.95) {
					Vector albedo = { Random(0.5, 1), Random(0.5, 1), Random(0.5, 1) };
					double fuzz = Random(0, 0.5);
					material = std::make_shared<Metal>(Vector(albedo), fuzz);
					scene.AddObject(std::make_shared<Sphere>(Sphere(center, 0.2, material)));
				}

				else {
					material = std::make_shared<Glass>(1.5);
					scene.AddObject(std::make_shared<Sphere>(Sphere(center, 0.2, material)));
				}
			}
		}
	}

	auto material1 = std::make_shared<Glass>(1.5);
	auto material2 = std::make_shared<Lambertian>(Vector{ 0.4, 0.2, 0.1 });
	auto material3 = std::make_shared<Metal>(Vector(0.7, 0.6, 0.5), 0.0);

	scene.AddObject(std::make_shared<Sphere>(Vector(0, 1, 0), 1.0, material1));
	scene.AddObject(std::make_shared<Sphere>(Vector(-4, 1, 0), 1.0, material2));
	scene.AddObject(std::make_shared<Sphere>(Vector(4, 1, 0), 1.0, material3));

	return scene;
}

int main() {
	Image image(WIDTH, HEIGHT);
	Vector lookFrom = { 13, 2, 3 };
	Vector lookAt = { 0, 0, 0 };
	double focusDistance = (lookAt - lookFrom).Length();
	Camera camera(lookFrom, lookAt, { 0, 1, 0 }, 20.0, aspectRatio, 0.1, 10);
	Scene scene = CreateRandomScene();

	auto t1 = std::chrono::high_resolution_clock::now();
	ConcurrentRenderer renderer(scene, 16, 120);
	renderer.RenderCurrentScene(camera, image);
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = t2 - t1;
	std::cout << std::format("[INFO] Render took {:.5f} seconds\n", diff.count());

	std::filesystem::current_path(std::filesystem::path("images"));
	image.WriteImageTofile("simpleSphere.ppm");

	return 0;
}