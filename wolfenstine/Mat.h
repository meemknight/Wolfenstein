#pragma once


template<class T, int X, int Y>
struct Mat
{
	T *p;

	inline Mat() {	p = new T[X*Y];}

	inline T& at(int x, int y) { return p[x + y * X]; }

	inline int width() { return X; }
	inline int height() { return Y; }

	inline void cleanup() { delete[] p; }
};

