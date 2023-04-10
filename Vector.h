#pragma once

#include <ostream>

class Vector
{
public:
	Vector() : x{ 0.0 }, y{ 0.0 }, z{ 0.0 }, w{ 0.0 } {}
	Vector(double x, double y) : x{ x }, y{ y }, z{ 0.0 }, w{ 0.0 } {}
	Vector(double x, double y, double z) : x{ x }, y{ y }, z{ z }, w{ 0.0 } {}
	Vector(double x, double y, double z, double w) : x{ x }, y{ y }, z{ z }, w{ w } {}

	Vector(const Vector&) = default;
	Vector& operator= (const Vector&) = default;

	Vector operator+ (const Vector&) const;
	Vector& operator+= (const Vector&);
	Vector operator- (const Vector&) const;
	Vector& operator-= (const Vector&);
	Vector operator* (const double t) const;
	Vector& operator*= (const double t);
	Vector operator/ (const double t) const;
	Vector& operator/= (const double t);
	Vector operator~ () const;

	double Length() const;
	double LengthSquared() const;
	double DotProduct(const Vector&) const;
	Vector GetDirection() const;
	Vector& Normalize();
	Vector GetNormal() const;

	friend std::ostream& operator<<(std::ostream& out, const Vector&);

public:
	double x, y, z, w;
};