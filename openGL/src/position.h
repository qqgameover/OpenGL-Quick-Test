#pragma once
struct position
{
	int y;
	int x;
	position(int _y, int _x);
	position();
	position operator += (position rhs) const;
	position& operator += (const position* rhs);
};

