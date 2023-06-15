#include "ConcurrentRenderer.h"

#include <iostream>
#include <format>

void RenderBlock(Scene& scene, Camera& camera, Image& target, int startX, int startY, int blockSize);

ConcurrentRenderer::ConcurrentRenderer(Scene& scene, int threadCount, int blockSize) : renderThreads(threadCount), scene(scene), blockSize(blockSize)
{
}

void ConcurrentRenderer::RenderCurrentScene(Camera& camera, Image& target)
{
	for (int startY = 0; startY < target.GetHeight(); startY += blockSize)
	{
		for (int startX = 0; startX < target.GetWidth(); startX += blockSize)
		{
			renderThreads.Submit([&, startX, startY] {
				RenderBlock(scene, camera, target, startX, startY, blockSize);
				});
		}
	}
}

ConcurrentRenderer::~ConcurrentRenderer()
{
	renderThreads.~ThreadPool();
}

void RenderBlock(Scene& scene, Camera& camera, Image& target, int startX, int startY, int blockSize)
{
	std::cout << std::format("[INFO] Render ({}, {}) from thread: ", startX, startY) << std::this_thread::get_id() << '\n';
}
