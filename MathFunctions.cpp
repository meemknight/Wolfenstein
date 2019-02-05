#include "MathFunctions.h"

int getQuadrant(float a)
{
	
	if(a < 0)
	{
		a = -a;
		if (a > 2 * PI)
		{
			int period = a / (2 * PI);
			a -= period * (2 * PI);
		}

		if (a < PI / 2)
		{
			return 4;
		}

		if (a < PI)
		{
			return 3;
		}

		if (a < PI * 3.f / 4.f)
		{
			return 2;
		}

		return 1;
	}

	if(a > 2 * PI)
	{
		int period = a / (2 * PI);
		a -= period * (2 * PI);
	}
		
	if (a < PI / 2)
	{
		return 1;
	}

	if( a< PI)
	{
		return 2;
	}

	if(a < PI * 3.f / 4.f)
	{
		return 3;
	}
	
	return 4;


}

std::pair<float, float> intersect(float angle, float x, float y, float m2, float n2)
{
	float m1;
	float n1;
	m1 = tanf(angle);

	n1 = y - (m1 * x);

	return intersect(m1, n1, m2, n2);
}

std::pair<float, float> intersect(float m1, float n1, float m2, float n2)
{
	if(m1 - m2 == 0)
	{
		//just a big value whatever
		return { 100000.f , 100000.f };
	}

	float x = (n2 - n1) / (m1 - m2);
	float y = m1 * x + n1;
	return { x  , y };
}

float getDistance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
