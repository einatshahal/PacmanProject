#pragma once
#include "utils.h"
#include "Positions.h"
#include "board.h"
#include "ghosts.h"
#include"pacman.h"
#include"fruit.h"

class Game
{
private:

	bool find = false;
	int _state;//state mode for the game:1-for simple game, 2-for save game,3-for load game,4-for load silente game.
	vector <string> screen_files_name;
	vector <string> board_name;
	vector <Board> screen_files;
	bool color;//true-with color, false-black and white
	int firstScore; //first score in every level
	LEVEL levelghost = (LEVEL::BEST);

public:
	void setGame();                                                         //starting a new game
	void Run();
	void Menu() ;                                                        //printting the menu
	void printInstructions() const;                                     //printing the instructions of the game
	bool checkcollision(const Positions& object1, const Positions& object2); //check if the pacman and the ghost on the same positions
	void collisionPacmanGhost(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard);
	void menuColor();
	void setcolor(Pacman& pacman, vector<Ghost> &ghosts, Board& board, Fruit& fruit);                                            //check if the game will be in colors or black and white
	LEVEL levelmenu();
	void createGhosts(vector<Ghost> &vec, vector <Positions> &start_pos_ghosts,LEVEL level);
	void searchFiles(int num);
	void playGame(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard);
	void CreateFileSteps(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard, int timePoint);
	void CreateFileResult(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard);
	
	void setState(int state);
	int getState();
	void playLoadMode(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard);
	void playLoadSilentMode(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard);
	void LoadFileStepsVecs(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard);
	void LoadFileResultsVecs(Board& newBoard);
	void removeAllFiles();
};

