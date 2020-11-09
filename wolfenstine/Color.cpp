#include "Color.h"

std::ostream& operator<<(std::ostream &other, const Color &c)//todo
{
	other << c.r << " " << c.g << " " << c.b << " " << c.a << "\n";
	return other;
}

