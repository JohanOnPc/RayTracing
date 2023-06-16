#include "ConcurrentRenderer.h"

#include <iostream>
#include <format>
#include <chrono>
#include <format>

#include "Vector.h"
#include "Utilities.h"

void RenderBlock(Scene& scene, Camera& camera, Image& target, int startX, int startY, int blockSize);
Vector RayColor(const Ray& ray, const Scene& scene, int depth);

ConcurrentRenderer::ConcurrentRenderer(Scene& scene, int threadCount, int blockSize) : renderThreads(threadCount), scene(scene), blockSize(blockSize)
{
}

void ConcurrentRenderer::RenderCurrentScene(Camera& camera, Image& target)
{
	int currentBlock = 0;
	for (int startY = 0; startY < target.GetHeight(); startY += blockSize) {
		for (int startX = 0; startX < target.GetWidth(); startX += blockSize) {
			renderThreads.Submit([&, startX, startY, currentBlock] {
				auto t1 = std::chrono::high_resolution_clock::now();
				RenderBlock(scene, camera, target, startX, startY, blockSize);
				auto t2 = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> diff = t2 - t1;
				std::cout << std::format("[INFO] Rendered block {} in {:.5f} seconds\n", currentBlock, diff.count());
				});
			currentBlock++;
		}
	}

	renderThreads.WaitTillDone();
}

ConcurrentRenderer::~ConcurrentRenderer()
{
	renderThreads.~ThreadPool();
}

constexpr auto samples = 16;
constexpr auto maxDepth = 200;

void RenderBlock(Scene& scene, Camera& camera, Image& target, int startX, int startY, int blockSize)
{
	int width = target.GetWidth();
	int height = target.GetHeight();

	for (int y = startY; y < startY + blockSize; y++) {
		for (int x = startX; x < startX + blockSize; x++) {
			Vector color;
			for (int i = 0; i < samples; i++) {
				double u = (double(x) + Random()) / (width - 1);
				double v = (double(y) + Random()) / (height - 1);
				color += RayColor(camera.GetRay(u, v), scene, maxDepth);
			}

			double sampleFactor = 1.0 / samples;
			target.WritePixel(x, y, color * sampleFactor);
		}
	}
}

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
