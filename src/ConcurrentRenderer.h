#pragma once

#include "ThreadPool.h"
#include "Scene.h"
#include "Camera.h"
#include "Image.h"

class ConcurrentRenderer
{
public:
	ConcurrentRenderer(Scene& scene, int threadCount, int blockSize);
	void RenderCurrentScene(Camera& camera, Image& target);
	~ConcurrentRenderer();

private:
	ThreadPool renderThreads;
	Scene scene;
	int blockSize;
};

