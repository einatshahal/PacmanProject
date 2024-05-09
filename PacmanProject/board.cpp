#include "board.h"
#include "utils.h"

void Board::printBoard()const
{
	setTextColor(Color::WHITE);
	int col, row;

	for (row = 0; row < metrixboard.size(); row++)
	{
		for (col = 0; col < metrixboard[row].size(); col++)
		{
			if (metrixboard[row][col] == (char)Sign::GAME_INFO)
			{
				cout << (char)Sign::SPACE;
			}
			else if(metrixboard[row][col] == (char)Sign::TUNNEL)
			{
				cout << (char)Sign::SPACE;
			}
			else
			{
				cout << this->metrixboard[row][col];
			}
		}
		cout << endl;
	}
}

void Board::printLivesAndScore(const int& lives, const int& score, const int& bonus)const
{
	setTextColor(this->_colorline);
	gotoxy(_livesAndScore.getX(),_livesAndScore.getY());
	cout << "LIVES:" << lives << "   SCORE:" << (score + bonus);
}

void Board::printPause()const
{
	setTextColor(this->_colorpause);
	gotoxy(_livesAndScore.getX(), _livesAndScore.getY()+1); 
	cout << "Game paused";
	gotoxy(_livesAndScore.getX(), _livesAndScore.getY() + 2);
	cout << "press ESC";
	setTextColor(Color::WHITE);
}

void Board::changeBoard(const Positions& pos)
{
	if ((pos.getX() == 0) || (pos.getY() == 0) || pos.getY() == (this->_screen_row - 1) || pos.getX() == (this->_screen_col - 1))
	{
		this->metrixboard[pos.getY()][pos.getX()] = (char)Sign::TUNNEL;
	}
	else
	{
		this->metrixboard[pos.getY()][pos.getX()] = (char)Sign::SPACE;
	}
}

void Board::setTotalFood()
{
	int col, row;

	int count = 0;
	for (col = 0; col < metrixboard.size(); col++)
	{
		for (row = 0; row <metrixboard[col].size(); row++)
		{
			if (this->metrixboard[col][row] == (char)Sign::FOOD)
			{
				count++;
			}
		}
	}
	this->_totalfood = count;
}

int Board::getTotalFood() const
{
	return (this->_totalfood);
}

char Board::getCharFromBoard(const Positions& pos)const
{
	char ch;
	ch = (this->metrixboard[pos.getY()][pos.getX()]);
	return ch;
}

void Board::printprevpos(const Positions& pos, const char& c)const
{
	if (c == (char)Sign::PACMAN)
	{
		gotoxy(pos.getX(), pos.getY());
		cout << (char)Sign::SPACE;
	}
	else
	{
		gotoxy(pos.getX(), pos.getY());
		setTextColor(Color::WHITE);
		cout << getCharFromBoard(pos);
	}
}

void Board::setColor(bool c)
{
	if (c == TRUE)
	{
		this->_colorline = Color::LIGHTMAGENTA;
		this->_colorpause = Color::RED;
		this->_colorboard = Color::WHITE;
	}
	else 
	{
		this->_colorline = Color::WHITE;
		this->_colorpause = Color::WHITE;
		this->_colorboard = Color::WHITE;
	}
}

Color Board::getColorline() const
{
	return (this->_colorline);
}

int Board::getCol()
{
	return this->_screen_col;
}

int Board::getRow()
{
	return this->_screen_row;
}

void Board::createBoard(string& screen_board_name,Positions &_pos_pacman,vector <Positions> &_pos_ghosts, string& board_name)
{
	this->boardName = board_name;
	_livesAndScore.setX(-10);//col
	_livesAndScore.setY(-10);//row

	ifstream myfile(screen_board_name, ios_base::in);//open the file
	char c;
	int row = 0;

	while (!myfile.eof() && (row <26))
	{
		int i;
		int col = 0;
		myfile.get(c);//get the first char in the row
		vector<char> temp;//row

		while ((c != '\n') && !myfile.eof() && (col < 81))//read line
		{
			if ((row ==( _livesAndScore.getY() + 1) )&& col == _livesAndScore.getX())
			{
				for (i = 0; i < 20; i++)
				{
				temp.push_back((char)Sign::GAME_INFO);
				col++;
				}
				myfile.seekg(19,ios::cur);
			}
			else if ((row == (_livesAndScore.getY() + 2)) && col == _livesAndScore.getX())
			{
				for (i = 0; i < 20; i++)
				{
					temp.push_back((char)Sign::GAME_INFO);
					col++;
				}
				myfile.seekg(19, ios::cur);
			}
			else if (c == '%')
			{
				temp.push_back((char)Sign::SPACE);
			}
			else if (c == (char)Sign::WALL)
			{
				temp.push_back(c);
			}
			else if (c == (char)Sign::SPACE)
			{
				temp.push_back((char)Sign::FOOD);
			}
			else if (c == (char)Sign::PACMAN)
			{
				temp.push_back((char)Sign::SPACE);
				_pos_pacman.setX(temp.size());
				_pos_pacman.setY(metrixboard.size());
			}
			else if (c == (char)Sign::GHOST)
			{
				temp.push_back((char)Sign::SPACE);

				Positions pos;
				pos.setX(temp.size());
				pos.setY(metrixboard.size());
				_pos_ghosts.push_back(pos);
			}
			else if (c == '&')
			{
				_livesAndScore.setX(temp.size());//col
				_livesAndScore.setY(metrixboard.size());//row

				for (i = 0; i < 20; i++)
				{
					temp.push_back((char)Sign::GAME_INFO);
					col++;
				}
				myfile.seekg(19, ios::cur);
			}

			myfile.get(c);
			col++;
		}

		if (row == 0)
		{
			this->_screen_col= temp.size();
		}
		else
		{
			while (col < this->_screen_col)
			{
				temp.push_back((char)Sign::SPACE);
				col++;
			}
		}

		this->_colorboard = Color::WHITE;
		this->_colorline = Color::WHITE;
		this->_colorpause = Color::WHITE;

		metrixboard.push_back(temp);//create row
		row++;
	}

	this->_screen_col = metrixboard[0].size();
	this->_screen_row = row;

myfile.close();//close the file.

defineTunnel();
}

Positions Board::get_livesAndScore()const
{
	return this->_livesAndScore;
}

void Board::defineTunnel()
{
	int col, row;

	for (row = 0; row < _screen_row; row++)
	{
		for (col = 0; col < _screen_col; col++)
		{
			if (row == 0 && metrixboard[row][col]==(char)Sign::SPACE)
			{
				if (metrixboard[(_screen_row-1)][col] == (char)Sign::SPACE)
				{
					metrixboard[row][col] = (char)Sign::TUNNEL;
					metrixboard[(_screen_row-1)][col] = (char)Sign::TUNNEL;
				}
			}

			if (col == 0 && metrixboard[row][col] == (char)Sign::SPACE)
			{
				if (metrixboard[row][(_screen_col-1)] == (char)Sign::SPACE)
				{
					metrixboard[row][col] = (char)Sign::TUNNEL;
					metrixboard[row][(_screen_col-1)] = (char)Sign::TUNNEL;
				}
			}
		}

	}

}

string Board::getnameBoard()
{
	return this->boardName;
}

void Board::setVectorresults(int pointTime)
{
	results.push_back(pointTime);
}

vector<int> Board::getVector()
{
	return this->results;
}