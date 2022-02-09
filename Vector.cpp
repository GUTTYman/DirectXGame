#include "Vector.h"
#include<math.h>

Vector2::Vector2()
	:Vector2(0, 0)
{}
Vector2::Vector2(float x, float y) : x(x), y(y)
{
}
float Vector2::length() const
{
	return(float)sqrt(x * x + y * y);
}
Vector2& Vector2::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return*this;
}
float Vector2::dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}
float Vector2::distance(const Vector2& v) const
{
	return sqrt((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
}
Vector2 Vector2::operator+() const
{
	return *this;
}
Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
Vector2& Vector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}
Vector2& Vector2::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}
const Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	return temp += v2;
}
const Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	return temp -= v2;
}
const Vector2 operator*(const Vector2& v, float s)
{
	Vector2 temp(v);
	return temp *= s;
}
const Vector2 operator*(float s, const Vector2& v)
{
	return v * s;
}
const Vector2 operator/(const Vector2& v, float s)
{
	Vector2 temp(v);
	return temp /= s;
}




Vector3::Vector3()
	:Vector3(0, 0, 0)
{}
Vector3::Vector3(float x, float y, float z):x(x),y(y),z(z)
{

}
float Vector3::length() const
{
	return(float)sqrt(x * x + y * y + z * z);
}
Vector3& Vector3::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return*this;
}
float Vector3::dot(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}
float Vector3::distance(const Vector3& v) const
{
	return sqrt((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y) + (v.z - z) * (v.z - z));
}
Vector3 Vector3::cross(const Vector3& v) const
{
	return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3 Vector3::operator+() const
{
	return *this;
}
Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}
const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp += v2;
}
const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}
const Vector3 operator*(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp *= s;
}
const Vector3 operator*(float s, const Vector3& v)
{
	return v * s;
}
const Vector3 operator/(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp /= s;
}

const Vector3 lerp(const Vector3& start, const Vector3& end, float time)
{
	return start * (1.0f - time) + end * time;
}

const float lerp(const float& start, const float& end, float time)
{
	return start * (1.0f - time) + end * time;
}

const Vector3 easeIn(const Vector3& start, const Vector3& end, float time)
{
	return start * (1.0f - time * time) + end * time * time;
}

const Vector3 easeOut(const Vector3& start, const Vector3& end, float time)
{
	return start * (1.0f - time * (2.0f - time)) + end * time * (2.0f - time);
}

const  Vector3 easeInOut(const Vector3& start, const Vector3& end, float time)
{
	return start * (1.0f - (time * time) * (3.0f - 2.0f * time)) + end * (time * time) * (3.0f - 2.0f * time);
}

const Vector3 Repulsion(const Vector3& direction, const Vector3& p1, const Vector3& p2,float power)
{
	Vector3 line = p2 - p1;
	Vector3 a = Vector3(-line.y, line.x, 0);
	a = a.normalize();
	Vector3 L = -direction;
	float LdotNx2 = power * L.dot(a);
	Vector3 g = LdotNx2 * a - L;
	return g;
}
