#pragma once
#include "utils.h"
#include "Positions.h"
#include "board.h"


class GameObject
{
protected:
	Color _color;
	Positions _pos;
	Direction _dir;
	Sign _c; //&,$,5-9
	vector<int>steps;

public:
	GameObject(int x, int y, Sign newSign);   //ctor              

	Positions getpos() const;                 //returns the position of the object
	void setpos(int x, int y);               //set a new position by copy pos                 
	void setColor(Color c);                   //set the color of the object
	Color getColor() const;                   //returns the color of the object
	Positions direction(Direction dir);
	Direction getdir() const;
	void setdir(Direction dir);
	void randir();
	//void moveGhostFruit(int row, int col);  //change the direction of the ghost and the fruit ,if the next move is a wall or tunnel
	Sign getSign() const;
	void setSign(char sign);
	void printObject() const;
	void moveRandom(const Board& board);  //change the direction of the ghost and the fruit ,if the next move is a wall or tunnel
	void moveByDirInLoadMode(Direction dir);
	void setVectorSteps(int dir);
	vector<int> getVector();
	void initSteps();
};