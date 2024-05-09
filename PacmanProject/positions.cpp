#include "positions.h"

Positions::Positions()
{
	this->_x = 0;
	this->_y = 0;
}

Positions::Positions(const Positions& pos)
{
	this->_x = pos._x;
	this->_y = pos._y;
}

void Positions::setX(int x)
{
	this->_x = x;
}

void Positions::setY(int y)
{
	this->_y = y;
}

int Positions::getX() const
{
	return(this->_x);
}

int Positions::getY() const
{
	return(this->_y);
}

void Positions::setPosition(Positions pos)
{
	this->setX(pos.getX());
	this->setY(pos.getY());
}