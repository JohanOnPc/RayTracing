#include "ConcurrentRenderer.h"

#include <iostream>
#include <format>

#include "Vector.h"

void RenderBlock(Scene& scene, Camera& camera, Image& target, int startX, int startY, int blockSize);

ConcurrentRenderer::ConcurrentRenderer(Scene& scene, int threadCount, int blockSize) : renderThreads(threadCount), scene(scene), blockSize(blockSize)
{
}

void ConcurrentRenderer::RenderCurrentScene(Camera& camera, Image& target)
{
	for (int startY = 0; startY < target.GetHeight(); startY += blockSize) {
		for (int startX = 0; startX < target.GetWidth(); startX += blockSize) {
			renderThreads.Submit([&, startX, startY] {
				RenderBlock(scene, camera, target, startX, startY, blockSize);
				});
		}
	}

	renderThreads.WaitTillDone();
}

ConcurrentRenderer::~ConcurrentRenderer()
{
	renderThreads.~ThreadPool();
}

void RenderBlock(Scene& scene, Camera& camera, Image& target, int startX, int startY, int blockSize)
{
	for (int y = startY; y < startY + blockSize; y++) {
		for (int x = startX; x < startX + blockSize; x++) {

		}
	}

	std::this_thread::sleep_for(std::chrono::duration<double>(0.001));
}
