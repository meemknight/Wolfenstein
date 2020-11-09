#pragma once

__declspec(align(16))
class Vector
{
public:
	Vector() = default;
	Vector(float x, float y, float z, float w):x(x), y(y), z(z), w(w){}

	float x, y, z, w;
	
};

