#pragma once
#include <atltypes.h>
#include <iostream>

__declspec(align(4)) struct Color
{
	Color() = default;
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0):r(r), g(g), b(b), a(a){}
	Color(UINT32 color):color(color) {}

	union 
	{
		UINT32 color;
		struct
		{
			UCHAR r, g, b, a;
		};
	};

	static inline Color black() { return Color(0); }
	static inline Color white() { return Color(MAXUINT32); }
	static inline Color red() { return Color(UCHAR_MAX, 0, 0, 0); }
	static inline Color green() { return Color(0, UCHAR_MAX, 0, 0); }
	static inline Color blue() { return Color(0, 0, UCHAR_MAX, 0); }


};

