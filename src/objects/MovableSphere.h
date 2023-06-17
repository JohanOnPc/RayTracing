#pragma once

#include "../Vector.h"
#include "../Ray.h"
#include "Hittable.h"

class MovableSphere :
	public Movable
{
public:
	MovableSphere() : originStart{}, originEnd{}, radius{ 1.0 }, timeStart{ 0.0 }, timeEnding{ 0.0 }, material{ nullptr } {}
	MovableSphere(Vector originStart, Vector originEnd, double timeStart, double timeEnding, double radius, std::shared_ptr<Material> material) :
		originStart{ originStart }, originEnd{ originEnd }, timeStart{ timeStart }, timeEnding{ timeEnding }, radius{ radius }, material{ material } {}

	virtual bool IsHitByRay(const Ray& ray, double tMin, double tMax, HitRecord& hit) const override;
	virtual Vector GetCenterAtTime(double time) const override;

public:
	std::shared_ptr<Material> material;
	Vector originStart, originEnd;
	double radius;
	double timeStart, timeEnding;
};

