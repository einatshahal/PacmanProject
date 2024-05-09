#include "pacman.h"
#include "board.h"
#include "utils.h"

Pacman::Pacman(Sign newSign):GameObject(0, 0, newSign)
{
	this->setpos(0, 0);
	this->StartPos.setX(0);
	this->StartPos.setY(0);
	this->lives = 3;
	this->score = 0;
	this->speed = 1000;
	this->bonus = 0;
}

void Pacman::changePacman(int lives, int score)
{
	setpos(StartPos.getX(),StartPos.getY());
	this->lives = lives;
	this->score = score;
}

void Pacman::changeLives()
{
	(this->lives)--;
}

int Pacman::getlives() const
{
	return (this->lives);
}

void Pacman::addScore(int scoreAdd)
{
	this->score = score + scoreAdd;
}

int Pacman::getscore() const
{
	return (this->score);
}

bool Pacman::move(Direction dir, Board& board)
{
	Positions nextpos(this->getpos());
	nextpos = direction(dir);

	if (board.getCharFromBoard(nextpos) == (char)Sign::WALL)
	{
		return false;
	}

	else if (board.getCharFromBoard(nextpos) == (char)Sign::TUNNEL)
	{
		Positions tempPos;

		if (dir == Direction::RIGHT1 || dir == Direction::RIGHT2)
		{
			tempPos.setY(nextpos.getY());
			tempPos.setX(1);
		}
		else if (dir == Direction::LEFT1 || dir == Direction::LEFT2) 
		{
			tempPos.setY(nextpos.getY());
			tempPos.setX(board.getCol()-1);
		}
		else if (dir == Direction::UP1 || dir == Direction::UP2) 
		{
			tempPos.setY(board.getRow()-1);
			tempPos.setX(nextpos.getX());
		}
		else if (dir == Direction::DOWN1 || dir == Direction::DOWN2)
		{
			tempPos.setY(1);
			tempPos.setX(nextpos.getX());
		}

		if (board.getCharFromBoard(tempPos) == (char)Sign::WALL || board.getCharFromBoard(tempPos) == (char)Sign::GAME_INFO)
		{
			this->setpos(nextpos.getX(), nextpos.getY());
			return false;
		}
		else
		{
			nextpos.setPosition(tempPos);
		}
		
	}

	else if (board.getCharFromBoard(nextpos) == (char)Sign::SPACE && ((nextpos.getX() == 0) || (nextpos.getY() == 0) || nextpos.getX() == (board.getCol() - 1) || nextpos.getY() == (board.getRow() - 1)))
	{
		return false;
	}
	else if (board.getCharFromBoard(nextpos) == (char)Sign::GAME_INFO)
	{
		return false;
	}

	this->_dir = dir;
	this->setpos(nextpos.getX(),nextpos.getY());
	return true;
}

void Pacman::moveInLoadMode(Direction dir, Board& board)
{
	Positions nextpos(this->getpos());
	nextpos = direction(dir);

}

void Pacman::setbonus(int num)
{
	this->bonus = bonus + num;
}

int Pacman::getbonus() const
{
	return bonus;
}

void Pacman::setPosStart(const Positions pos)
{
	this->StartPos.setPosition(pos);
	this->_pos.setPosition(pos);
}
