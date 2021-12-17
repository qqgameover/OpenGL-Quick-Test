#include "position.h"
position::position(int y, int x)
{
	this->y = y;
	this->x = x;
}
position::position()
{
	y = 0;
	x = 0;
}
position position::operator += (const position rhs) const
{
	return { y + rhs.y, x + rhs.x };
}
position& position::operator +=(const position* rhs)
{
	this->x += rhs->x;
	this->y += rhs->y;
	return *this;
}
