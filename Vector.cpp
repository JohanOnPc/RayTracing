#include "Vector.h"
#include <math.h>

Vector Vector::operator+ (const Vector& vec) const 
{
	return Vector(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

Vector& Vector::operator+= (const Vector& vec)
{
	*this = *this + vec;
	return *this;
}

Vector Vector::operator- (const Vector& vec) const
{
	return Vector(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

Vector& Vector::operator-= (const Vector& vec)
{
	*this = *this - vec;
	return *this;
}

Vector Vector::operator* (const double t) const
{
	return Vector(x * t, y * t, z * t, w * t);
}

Vector& Vector::operator*= (const double t)
{
	*this = *this * t;
	return *this;
}

Vector Vector::operator/ (const double t) const
{
	return Vector(x / t, y / t, z / t, w / t);
}

Vector& Vector::operator/= (const double t)
{
	*this = *this / t;
	return *this;
}

Vector Vector::operator~ () const
{
	return Vector() - *this;
}

double Vector::LengthSquared() const
{
	return x * x + y * y + z * z + w * w;
}

double Vector::Length() const
{
	return sqrt(LengthSquared());
}

double Vector::DotProduct(const Vector& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

std::ostream& operator<<(std::ostream& out, const Vector& vec)
{
	return out << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
}
