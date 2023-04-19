#include "Scene.h"

void Scene::AddObject(std::shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

bool Scene::IsHitByRay(const Ray& ray, double tMin, double tMax, HitRecord& hit) const
{
	bool isHit = false;
	double closest = tMax;

	for (const auto& object : objects) {
		if (object->IsHitByRay(ray, tMin, closest, hit)) {
			isHit = true;
			closest = hit.t;
		}
	}

	return isHit;
}
