#include "Vector.h"
#include <math.h>

#include "Utilities.h"

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

Vector Vector::operator*(const Vector& vec) const
{
	return Vector(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}

Vector& Vector::operator*=(const Vector& vec)
{
	*this = *this * vec;
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

Vector Vector::GetDirection() const
{
	return *this / Length();
}

Vector& Vector::Normalize()
{
	*this /= Length();
	return *this;
}

Vector Vector::GetNormal() const
{
	return *this / Length();
}

bool Vector::IsNearZero(double e) const
{
	return (abs(x) < e) && (abs(y) < e) && (abs(z) < e) && (abs(w) < e);
}

Vector Vector::GetRandom(double min, double max)
{
	return Vector(Random(min, max), Random(min, max), Random(min, max));
}

Vector Vector::GetRandomVectorInUnitSphere()
{
	while (true) {
		Vector vec = Vector::GetRandom(-1.0, 1.0);
		if (vec.LengthSquared() < 1.0) {
			return vec;
		}
	}
}

Vector Vector::CrossProduct3D(const Vector& vec1, const Vector& vec2)
{
	return Vector(vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x);
}

Vector operator*(const double t , const Vector& vec) 
{
	return vec * t;
}

double DotProduct(const Vector& vec1, const Vector& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w;
}

std::ostream& operator<<(std::ostream& out, const Vector& vec)
{
	return out << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
}