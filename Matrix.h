#pragma once
#include<Vector2.h>
const int kRowHeight = 20;
const int kColumnWidth = 64;

struct Matrix2x2
{
	float m[2][2];
};

struct Matrix3x3
{
	float m[3][3];
};

template<typename T>
T Clamp(T num, T min, T max)
{
	if (num < min) { return min; }
	if (num > max) { return max; }
	return num;
}