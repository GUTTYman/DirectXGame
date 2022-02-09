#pragma once

struct Vector2
{
	float x, y;//XYê¨ï™

	Vector2();
	Vector2(float x, float y);

	float length()const;
	Vector2& normalize();
	float dot(const Vector2& v)const;
	float distance(const Vector2& v)const;
	Vector2 operator+() const;
	Vector2 operator-() const;

	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);

};
struct Vector3
{
	float x, y, z;//XYZê¨ï™

	Vector3();
	Vector3(float x, float y, float z);

	float length()const;
	Vector3& normalize();
	float dot(const Vector3& v)const;
	float distance(const Vector3& v)const;
	Vector3 cross(const Vector3& v)const;

	Vector3 operator+() const;
	Vector3 operator-() const;

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);

};

const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);


const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);

const Vector3 lerp(const Vector3& start, const Vector3& end, float time);
const float lerp(const float& start, const float& end, float time);
const Vector3 easeIn(const Vector3& start, const Vector3& end, float time);
const Vector3 easeOut(const Vector3& start, const Vector3& end, float time);
const Vector3 easeInOut(const Vector3& start, const Vector3& end, float time);
const Vector3 Repulsion2(const Vector3& direction, const Vector3& p1, const Vector3& p2,float power);
const Vector3 Repulsion(const Vector3& direction, const Vector3& normal,float power);
