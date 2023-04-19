#pragma once

#include <vector>
#include <memory>

#include "objects/Hittable.h"

class Scene
{
public:
	Scene() {}

	Scene(const Scene&) = default;
	Scene& operator= (const Scene&) = default;

	void AddObject(std::shared_ptr<Hittable>);
	bool IsHitByRay(const Ray&, double, double, HitRecord&) const;

private:
	std::vector<std::shared_ptr<Hittable>> objects;
};

