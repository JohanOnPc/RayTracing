#pragma once

#include "Material.h"

class Metal :
    public Material
{
public:
    Metal(const Vector& color, double fussiness) : albedo{color}, fussiness{fussiness} {}

    virtual bool ScatterRay(const Ray& ray, const struct HitRecord& hit, Vector& attenuation, Ray& scattered) const override;

public:
    Vector albedo;
    double fussiness;
};

