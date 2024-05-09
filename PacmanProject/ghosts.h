#pragma once
#include "utils.h"
#include "positions.h"
#include "board.h"
#include "gameObject.h"

class Ghost:public GameObject
{
private:
	LEVEL _level;
	Positions StartPos;
	int countmoves; //only on the good and novice levels - count the 5 steps that the ghost is not smart on good level, and count 20 moves on novice level
	int moveChange; //only on the good level - rand number between 1 to 20, in this move of the ghost it turn to rand moves
	int countspeedGhost;
public:
	Ghost(int x, int y, LEVEL level);
	void initStartPos(int x, int y);
	void changeGhost();
	void ghostMove(const Positions& pacPos, const Board& board);
	void moveNovice(const Positions& pacPos, const Board& board);
	void moveGood(const Positions& pacPos, const Board& board);
	void moveBest(const Positions& pacPos, const Board& board);

	void initCountMove();
	bool checkNextMoveGhost(int x, int y, const Board& board);
	void setGhostSpeedCount(int num);
	int getGhostSpeedCount();

	void setLevel(LEVEL newLevel);
};
