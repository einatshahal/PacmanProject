#pragma once
#include "utils.h"
#include "Positions.h"
#include "gameObject.h"

class Pacman :public GameObject
{
private:
	Positions StartPos;
	int lives;         
	int score;//bread  
	int bonus; 
	int speed; 
 
public:
	Pacman(Sign newSign);//ctor

	void changePacman(int lives, int score);  //saving the new score, update the lives and set the position
	void changeLives();                       //loses one life
	void addScore(int scoreAdd);                          //add one score when the pacman eats bread
	int getlives() const;                     //returns the current lifes 
	int getscore() const;
	void setbonus(int num);
	int getbonus() const;
	bool move(Direction dir, Board& board);                  //one move of pacman by the direction 
	void moveInLoadMode(Direction dir, Board& board);
	void setPosStart(const Positions pos);
};
