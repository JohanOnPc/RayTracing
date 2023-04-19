#pragma once

#include "Material.h"
#include "../Vector.h"

class Lambertian :
    public Material
{
public:
    Lambertian(const Vector& color) : albedo{color} {}

    virtual bool ScatterRay(const Ray& ray, const struct HitRecord& hit, Vector& attenuation, Ray& scattered) const override;

public:
    Vector albedo;
};