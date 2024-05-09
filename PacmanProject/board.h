#pragma once
#include "utils.h"
#include "Positions.h"

class Board
{
private:
	vector<vector<char>> metrixboard;
	vector<int>results;

	string boardName;
	Color _colorline;
	Color _colorboard;
	Color _colorpause;


	Positions _livesAndScore;

	int _totalfood;
	int _numghosts;

	int _screen_row;
	int _screen_col;
public:
	
	void printBoard()const;                                        //Prints the board
	void printLivesAndScore(const int& lives, const int& score, const int& bonus)const;                    //prints the lives and the score of the pacman
	void printPause()const;
	void changeBoard(const Positions& pos);                                        //change the board after the pacman eats food 
	void setTotalFood();                                                                //counts how many food are on the board
	int getTotalFood() const;                                                                //counts how many food are on the board
	char getCharFromBoard(const Positions& pos) const;                                 //get the char from the board in the position pos
	void printprevpos(const Positions& pos, const char& c)const;                     //if the pacman was in this position before print space, if the ghost was, print the char from the board
	void setColor(bool c);
	Color getColorline() const;
	int getCol();
	int getRow();
	void createBoard(string& screen_board_name, Positions& _pos_pacman, vector <Positions>& _pos_ghosts, string& board_name);
	Positions get_livesAndScore()const;
	void defineTunnel();
	string getnameBoard();
	void setVectorresults(int pointTime);
	vector<int> getVector();

};

