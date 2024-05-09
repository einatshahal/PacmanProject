#include "fruit.h"



Fruit::Fruit(int x, int y, Sign newSign) :GameObject(x, y, newSign)
{
	randFruitNum();
	this->show = TRUE;
	randir();
}

void Fruit::randFruitNum()
{
	srand((unsigned)time(NULL));
	int c = rand() % 5 + 5;
	this->_c = (Sign)(c + '0');
}


//this function returns the number of the fruit
int Fruit::getFruitNum() const
{
	return ((char)this->_c - '0');
}

//this function sets rand pos
void Fruit::setrandposfruit(Board& newBoard)
{
	int x, y;
	do
	{
		srand((unsigned)time(NULL));
		y = rand() % (newBoard.getRow());
		x = rand() % (newBoard.getCol());
		this->setpos(x, y);
	} while ((newBoard.getCharFromBoard(this->getpos()) != (char)Sign::SPACE) && (newBoard.getCharFromBoard(this->getpos()) != (char)Sign::FOOD));

	return;
}

void Fruit::setShow(bool b)
{
	this->show = b;
}

bool Fruit::getShow() const
{
	return(this->show);
}

void Fruit::printFruit() const
{
	setTextColor(this->getColor());
	gotoxy(this->getpos().getX(), this->getpos().getY());
	cout << (char)this->_c;

}

void Fruit::setSpeedFruitCount(int num)
{
	this->countSpeedFruit = num;
}

int Fruit::getSpeedFruitCount()
{
	return(this->countSpeedFruit);
}



void Fruit::setVecShow(int num)
{
	this->vecShow.push_back(num);
}

vector<int> Fruit::getVecShow()
{
	return this->vecShow;
}

void Fruit::initVecShow()
{
	(this->vecShow).clear();
}



void Fruit::setVecValue(char sign)
{
	this->vecValue.push_back(sign);
}
vector<char> Fruit::getVecValue()
{
	return this->vecValue;
}
void Fruit::initVecValue()
{
	(this->vecValue).clear();
}



void Fruit::setVecPositions(int x, int y)
{
	Positions pos;
	pos.setX(x);
	pos.setY(y);
	this->vecPosition.push_back(pos);
}
vector<Positions> Fruit::getVecPositions()
{
	return this->vecPosition;
}
void Fruit::initVecPositions()
{
	(this->vecPosition).clear();
}

