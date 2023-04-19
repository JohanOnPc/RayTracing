#pragma once

#include "Material.h"

class Metal :
    public Material
{
public:
    Metal(const Vector& color, double fuzziness) : albedo{color}, fuzziness{fuzziness < 1.0 ? fuzziness : 1.0} {}

    virtual bool ScatterRay(const Ray& ray, const struct HitRecord& hit, Vector& attenuation, Ray& scattered) const override;

public:
    Vector albedo;
    double fuzziness;
};