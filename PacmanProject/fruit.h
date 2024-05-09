#pragma once
#include "utils.h"
#include "positions.h"
#include "board.h"
#include "gameObject.h"

class Fruit :public GameObject
{
private:
	bool show;
	int countSpeedFruit;
	vector<int>vecShow; //vector with the numbers 1 or 0
	vector<char>vecValue; //vector with the value of the fruit (5-9)
	vector<Positions>vecPosition;//vector with the positions of the fruit
public:

	Fruit(int x, int y, Sign newSign);
	void randFruitNum();
	int getFruitNum() const;
	void setrandposfruit(Board& newBoard);
	void printFruit() const;
	void setShow(bool b);
	bool getShow() const;
	void setSpeedFruitCount(int num);
	int getSpeedFruitCount();

	void setVecShow(int num);
	vector<int> getVecShow();
	void initVecShow();

	void setVecValue(char sign);
	vector<char> getVecValue();
	void initVecValue();

	void setVecPositions(int x, int y);
	vector<Positions> getVecPositions();
	void initVecPositions();
};
