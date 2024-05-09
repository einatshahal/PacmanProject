#pragma once
#include "utils.h"

class Positions
{
private:
	int _x;
	int _y;

public:
	Positions();
	Positions(const Positions& pos);

	void setX(int x);                //change the x on the position
	int getX() const;                      //returns the x of the position
	void setY(int y);                //change the y on the position
	int getY() const;                      //returns the y of the position
	void setPosition(Positions pos); //change the position, x and y, by copy position

};

