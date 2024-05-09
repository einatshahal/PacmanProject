#include "ghosts.h"
#include "board.h"
#include "utils.h"


Ghost::Ghost(int x, int y, LEVEL level):GameObject(x, y, Sign::GHOST)
{
	this->StartPos.setX(x);
	this->StartPos.setY(y);
	this->_dir = Direction::UP1;
	this->_level = level;
	countmoves = 0;
	moveChange = 0;
	countspeedGhost = 0;
}

void Ghost::initStartPos(int x, int y)
{
	this->StartPos.setX(x);
	this->StartPos.setY(y);
}

void Ghost::changeGhost()
{
	this->setpos(this->StartPos.getX(), this->StartPos.getY());
}

void Ghost::ghostMove(const Positions& pacPos, const Board& board)
{
	switch (this->_level)
	{

	case LEVEL::NOVICE:
	{
		moveNovice(pacPos, board);
		countspeedGhost++;
		break;
	}
	case LEVEL::GOOD:
	{
		moveGood(pacPos, board);
		break;
	}
	case LEVEL::BEST:
	{
		moveBest(pacPos, board);
		countspeedGhost++;
		break;
	}
	}
	return;
}

void Ghost::moveNovice(const Positions& pacPos, const Board& board)
{
	Positions nextpos;
	do
	{
		nextpos = direction(this->_dir);//define next pos with the direction

		if (board.getCharFromBoard(nextpos) == (char)Sign::WALL || board.getCharFromBoard(nextpos) == (char)Sign::TUNNEL || board.getCharFromBoard(nextpos) == (char)Sign::GAME_INFO||(this->countmoves == 20))
		{
			randir();
			nextpos = direction(this->_dir);//define next pos with the direction

		}

	} while (board.getCharFromBoard(nextpos) == (char)Sign::WALL || board.getCharFromBoard(nextpos) == (char)Sign::TUNNEL);

	if (countmoves == 20)
	{
		countmoves = 0;
	}
	else
	{
		countmoves++;
	}

	setpos(nextpos.getX(), nextpos.getY());
}


void Ghost::moveGood(const Positions& pacPos, const Board& board)
{
	if (this->moveChange == 0)
	{
		this->moveChange = rand() % 20;
	}

	if (this->moveChange == this->countspeedGhost)
	{
		if (this->countmoves != 5)
		{
			moveRandom(board);
			this->countmoves++;
		}
		else
		{
			moveRandom(board);
			this->countmoves = 0;
			this->moveChange = 0;
			this->countspeedGhost = 0;
		}
	}
	else
	{
		moveBest(pacPos, board);
		this->countspeedGhost++;
	}

}

void Ghost::moveBest(const Positions& pacPos, const Board& board)
{
	//static vector<Positions> forbidden;
	Positions tempPos;
	Direction tempDir;
	int minLenght = 10000;
	int currLenght;

	if (checkNextMoveGhost(this->getpos().getX() + 1, this->getpos().getY(), board) == true)
	{
		currLenght = pow((pacPos.getX()) - (this->getpos().getX() + 1), 2) + pow((pacPos.getY()) - (this->getpos().getY()), 2);
		if (currLenght < minLenght)
		{
			tempDir = Direction::RIGHT1;
			minLenght = currLenght;
		}
		if ((currLenght == minLenght) && (this->_dir == Direction::RIGHT1))
		{
			tempDir = Direction::RIGHT1;
			minLenght = currLenght;
		}
	}

	if (checkNextMoveGhost(this->getpos().getX() - 1, this->getpos().getY(), board) == true)
	{
		currLenght = pow((pacPos.getX()) - (this->getpos().getX() - 1), 2) + pow((pacPos.getY()) - (this->getpos().getY()), 2);
		if (currLenght < minLenght)
		{
			tempDir = Direction::LEFT1;
			minLenght = currLenght;
		}
		else if ((currLenght == minLenght) && (this->_dir == Direction::LEFT1))
		{
			tempDir = Direction::LEFT1;
			minLenght = currLenght;
		}
	}

	if (checkNextMoveGhost(this->getpos().getX(), this->getpos().getY() + 1, board) == true)
	{
		currLenght = pow((pacPos.getX()) - (this->getpos().getX()), 2) + pow((pacPos.getY()) - (this->getpos().getY() + 1), 2);
		if (currLenght < minLenght)
		{
			tempDir = Direction::DOWN1;
			minLenght = currLenght;
		}
		else if ((currLenght == minLenght) && (this->_dir == Direction::DOWN1))
		{
			tempDir = Direction::DOWN1;
			minLenght = currLenght;
		}
	}

	if (checkNextMoveGhost(this->getpos().getX(), this->getpos().getY() - 1, board) == true)
	{
		currLenght = pow((pacPos.getX()) - (this->getpos().getX()), 2) + pow((pacPos.getY()) - (this->getpos().getY() - 1), 2);
		if (currLenght < minLenght)
		{
			tempDir = Direction::UP1;
			minLenght = currLenght;
		}
		else if ((currLenght == minLenght) && (this->_dir == Direction::UP1))
		{
			tempDir = Direction::UP1;
			minLenght = currLenght;
		}
	}


	this->_dir = tempDir;
	tempPos = direction(_dir);
	this->setpos(tempPos.getX(), tempPos.getY());
}


void Ghost::initCountMove()
{
	this->countmoves = 0;
}

bool Ghost::checkNextMoveGhost(int x, int y, const Board& board)
{
	Positions pos;
	pos.setX(x);
	pos.setY(y);
	if (board.getCharFromBoard(pos) == (char)Sign::WALL || board.getCharFromBoard(pos) == (char)Sign::TUNNEL || board.getCharFromBoard(pos) == (char)Sign::GAME_INFO)
		return false;
	return true;
}


void Ghost::setGhostSpeedCount(int num)
{
	this->countspeedGhost = num;
}

int Ghost::getGhostSpeedCount()
{
	return(this->countspeedGhost);
}

void Ghost::setLevel(LEVEL newLevel)
{
	this->_level = newLevel;
}