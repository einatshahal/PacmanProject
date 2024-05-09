#include "gameObject.h"




GameObject::GameObject(int x, int y, Sign newSign)
{
	this->_dir = Direction::STAY1;
	this->_c = newSign;
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_color = Color::WHITE;
}

Positions GameObject::getpos() const
{
	Positions pos;
	pos.setX(this->_pos.getX());
	pos.setY(this->_pos.getY());
	return pos;
}

void GameObject::setpos(int x, int y)
{
	this->_pos.setX(x);
	this->_pos.setY(y);
}

void GameObject::setColor(Color c)
{
	this->_color = c;
}

Color GameObject::getColor() const
{
	return (this->_color);
}


Positions GameObject::direction(Direction dir)
{
	Positions nextpos(this->getpos());

	switch (dir)
	{
	case Direction::DOWN1:
		nextpos.setY((this->_pos.getY()) + 1);
		break;
	case Direction::DOWN2:
		nextpos.setY((this->_pos.getY()) + 1);
		break;
	case Direction::UP1:
		nextpos.setY((this->_pos.getY()) - 1);
		break;
	case Direction::UP2:
		nextpos.setY((this->_pos.getY()) - 1);
		break;
	case Direction::LEFT1:
		nextpos.setX((this->_pos.getX()) - 1);
		break;
	case Direction::LEFT2:
		nextpos.setX((this->_pos.getX()) - 1);
		break;
	case Direction::RIGHT1:
		nextpos.setX((this->_pos.getX()) + 1);
		break;
	case Direction::RIGHT2:
		nextpos.setX((this->_pos.getX()) + 1);
		break;
	}
	return(nextpos);
}


void GameObject::setdir(Direction dir)
{
	this->_dir = dir;
}

Direction GameObject::getdir() const
{
	return (this->_dir);
}

void GameObject::randir()
{
	int dir = rand() % 4;
	Direction c = Direction::UP1;

	if (dir == 1)
	{
		c = Direction::DOWN1;
	}
	else if (dir == 2)
	{
		c = Direction::LEFT1;
	}
	else if (dir == 3)
	{
		c = Direction::RIGHT1;
	}
	else if (dir == 4)
	{
		c = Direction::UP1;
	}

	setdir(c);
}


void GameObject::moveRandom(const Board& board)
{
	Positions nextpos;

	do
	{
		nextpos = direction(this->_dir);//define next pos with the direction

		if (board.getCharFromBoard(nextpos) == (char)Sign::WALL || board.getCharFromBoard(nextpos) == (char)Sign::TUNNEL || board.getCharFromBoard(nextpos) == (char)Sign::GAME_INFO)
		{
			randir();
			nextpos = direction(this->_dir);//define next pos with the direction
		}

	} while (board.getCharFromBoard(nextpos) == (char)Sign::WALL || board.getCharFromBoard(nextpos) == (char)Sign::TUNNEL || board.getCharFromBoard(nextpos) == (char)Sign::GAME_INFO);

	setpos(nextpos.getX(), nextpos.getY());
}

Sign GameObject::getSign() const
{
	return(this->_c);
}
void GameObject::setSign(char sign)
{
	if (sign == '@')
	{
		this->_c = Sign::PACMAN;
	}
	else if (sign == '$')
	{
		this->_c = Sign::GHOST;
	}
	else if (sign == '5')
	{
		this->_c = Sign::Fruit5;
	}
	else if (sign == '6')
	{
		this->_c = Sign::Fruit6;
	}
	else if (sign == '7')
	{
		this->_c = Sign::Fruit7;
	}
	else if (sign == '8')
	{
		this->_c = Sign::Fruit8;
	}
	else if (sign == '9')
	{
		this->_c = Sign::Fruit9;
	}
}

void GameObject::printObject() const
{
	setTextColor(this->getColor());
	gotoxy(this->getpos().getX(), this->getpos().getY());
	cout << (char)this->_c;
}

void GameObject::moveByDirInLoadMode(Direction dir)
{
	switch (dir)
	{
	case Direction::DOWN1:
		this->_pos.setY((this->_pos.getY()) + 1);
		break;
	case Direction::DOWN2:
		this->_pos.setY((this->_pos.getY()) + 1);
		break;
	case Direction::UP1:
		this->_pos.setY((this->_pos.getY()) - 1);
		break;
	case Direction::UP2:
		this->_pos.setY((this->_pos.getY()) - 1);
		break;
	case Direction::LEFT1:
		this->_pos.setX((this->_pos.getX()) - 1);
		break;
	case Direction::LEFT2:
		this->_pos.setX((this->_pos.getX()) - 1);
		break;
	case Direction::RIGHT1:
		this->_pos.setX((this->_pos.getX()) + 1);
		break;
	case Direction::RIGHT2:
		this->_pos.setX((this->_pos.getX()) + 1);
		break;
	}
}

void GameObject::setVectorSteps(int dir)
{
	this->steps.push_back(dir);
}

vector<int> GameObject::getVector()
{
	return this->steps;
}

void GameObject::initSteps()
{
	this->steps.clear();
}