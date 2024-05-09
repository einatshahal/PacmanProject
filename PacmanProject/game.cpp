#include "game.h"
#include "board.h"
#include "pacman.h"
#include "ghosts.h"
#include "utils.h"
#include "fruit.h"

void Game::setState(int state)
{
	this->_state = state;
}

int Game::getState()
{
	return(this->_state);
}

void Game::Run()
{
	if (this->_state == 1)
	{
		//the simple game
		Menu();
	}
	else if(this->_state == 2)
	{
		//save
		removeAllFiles();
		Menu();
	
	}
	else if (this->_state == 3)
	{
		//load
		searchFiles(1);
		if (find == true)
		{
			setGame();
			system("cls");
		}
		
	}
	else if (this->_state == 4)
	{
		//load slient
		searchFiles(1);
		if (find == true)
		{
			setGame();
		}
	
	}
}

void Game::Menu()
{
	system("cls");
	screen_files.clear();
	char choice;
	setTextColor(Color::WHITE);

	cout << " ___   _    ___  __  __    _    _  _ " << endl;
	cout << "| _ \\ /_\\  / __||  \\/  |  /_\\  | \\| |" << endl;
	cout << "|  _// _ \\| (__ | |\\/| | / _ \\ | .` |" << endl;
	cout << "|_| /_/ \\_\\\\___||_|  |_|/_/ \\_\\|_|\\_|" << endl << endl;

	cout << endl << "Menu Pacman Game:" << endl;
	cout << "press (1) for new game" << endl;
	cout << "press (2) for enter file game" << endl;
	cout << "press (8) for instructions" << endl;
	cout << "press (9) to exit" << endl;

	cin >> choice; //the choice of the player in the menu
	cout << endl;

	//if the choice of the player is invalid
	while (choice != '1' && choice != '8' && choice != '9' && choice != '2')
	{
		cout << "Invalid choice, please try again" << endl << endl;
		cin >> choice;
	}

	if (choice == '1') //start the game
	{
		searchFiles(1);

		if (find == true)
		{
			levelghost = levelmenu();
			menuColor();
			system("cls");
			setGame();
		}
		else
		{
			cout << "There is not any boards to load";
		}
	}

	else if (choice == '2') //chooce file 
	{
		searchFiles(2);

		if (find == true)
		{
			levelghost = levelmenu();
			menuColor();
			system("cls");
			setGame();
		}
		else
		{
			system("cls");
			cout << endl << "The required file was not found." << endl;
			Sleep(3000);

		}
	}

	//if the user wants to see the instructions
	else if (choice == '8')
	{
		printInstructions();
		while (_getch() != (char)Direction::ESC)
		{
		}
		Menu();
	}

	//exit
	else if (choice == '9')
	{
		system("cls");
		exit(0);
	}

}

void Game::printInstructions() const
{
	system("cls");
	cout << "Your player is Pacman - @." << endl << "The Pacman can be moved inside the maze using:" << endl << "Top - 'W' or 'w'" << endl << "Below - 'X' or 'x'" << endl << "Left - 'A' or 'a'" << endl << "Right - 'D' or 'd'" << endl << "Stay - 'S' or 's'" << endl << "Pause Game - 'ESC' " << endl;
	cout << "the Purpose of the game :" << endl << "Eat as much bread and fruit as possible(bonus)." << endl << "The bread and fruits eaten are accumulated from round to round." << endl << "Pacman is not allowed to touch ghosts, if he touches you will be disqualified." << endl << "3 disqualifications will result in the end of the game.";
	cout << endl << endl << "while you play the game, you can press 'g' to get out to the menu and finish the game." << endl << endl;
	cout << endl << "Press ESC for back to menu" << endl;
}

void Game::menuColor()
{
	int i;
	char color;
	system("cls");
	cout << "press (1) for colors" << endl;
	cout << "press (2) for BW" << endl;
	cin >> color;
	cout << endl;

	while (color != '1' && color != '2')
	{
		cout << "Invalid choice, please try again" << endl << endl;
		cin >> color;
	}

	if (color == '1')//color
	{
		this->color = true;
	}
	else if (color == '2')//BW
	{
		this->color = false;
	}
	system("cls");
}

void Game::setcolor(Pacman& pacman, vector<Ghost>& ghosts, Board& board, Fruit& fruit)
{
	int i;

	if (color == true)//color
	{
		pacman.setColor(Color::YELLOW);
		fruit.setColor(Color::LIGHTGREEN);
		board.setColor(TRUE);
		for (i = 0; i < ghosts.size(); i++)
		{
			ghosts[i].setColor(Color::LIGHTBLUE);
		}
		this->color = true;
	}
	else //color == false -BW
	{
		pacman.setColor(Color::WHITE);
		fruit.setColor(Color::WHITE);
		board.setColor(FALSE);
		for (i = 0; i < ghosts.size(); i++)
		{
			ghosts[i].setColor(Color::WHITE);
		}
		this->color = false;
	}
}

LEVEL Game::levelmenu()
{
	char level;
	system("cls");
	cout << "press (1) BEST level" << endl;
	cout << "press (2) GOOD level" << endl;
	cout << "press (3) NOVICE level" << endl;
	cin >> level;

	while (level != '1' && level != '2' && level != '3')
	{
		cout << "Invalid choice, please try again" << endl << endl;
		cin >> level;
	}
	if (level == '1')
		return LEVEL::BEST;
	if (level == '2')
		return LEVEL::GOOD;
	else
		return LEVEL::NOVICE;
}
	
void Game::createGhosts(vector<Ghost>& vec, vector<Positions>& start_pos_ghosts, LEVEL level)
{
	int i;
	for (i = 0; i < start_pos_ghosts.size(); i++)
	{
		Ghost ghost((start_pos_ghosts[i].getX()), (start_pos_ghosts[i].getY()), level);
		vec.push_back(ghost);
	}
}

void Game::searchFiles(int num)
{

	if (num == 1)
	{
		for (const auto& file : fs::directory_iterator("."))
		{

			if (file.path().extension() == (".screen"))
			{
				screen_files_name.push_back(file.path().string());
				board_name.push_back(file.path().stem().string());
				find = true;
			}
		}
	}

	else if (num == 2)
	{
	
		string game;
		system("cls");
		cout << "Enter the name file that you want to play" << endl;
		cin >> game;

		for (const auto& file : fs::directory_iterator("."))
		{
			if (file.path().filename() == (game))
			{
				screen_files_name.push_back(file.path().string());
				board_name.push_back(file.path().stem().string());
				find = true;
			}
		}
	
	}

}

void Game::setGame()
{
	int j=0;//num of screen
	Positions start_pos_pacman;
	vector <Positions> start_pos_ghosts;
	vector<Ghost> ghosts;

	Pacman pacman(Sign::PACMAN);
	Fruit fruit(0, 0, Sign::Fruit5);

	while (pacman.getlives() != 0 && (j < screen_files_name.size()) )
	{
		system("cls");
		firstScore = pacman.getscore();
		if (j != 0)
		{
			start_pos_ghosts.clear();
			ghosts.clear();
		}
		
		Board board;
		board.createBoard(screen_files_name[j], start_pos_pacman, start_pos_ghosts,board_name[j]);
		screen_files.push_back(board);
		screen_files[j].setTotalFood();//the max score
		pacman.setPosStart(start_pos_pacman);
		createGhosts(ghosts, start_pos_ghosts, levelghost);


		setcolor(pacman, ghosts, screen_files[j], fruit);

		if (this->_state == 1 || this->_state == 2)
		{
			playGame(pacman, ghosts, fruit, screen_files[j]);


			//the user los
			if (pacman.getlives() == 0)
			{
				system("cls");
				setTextColor(Color::WHITE);
				cout << "\n\n\n\n                       GAME OVER!!!!!!!!" << endl << endl;
				cout << "                      Press any key to return to the menu";
			}
			//the user win
			else if ((pacman.getscore() - firstScore == screen_files[j].getTotalFood()) )
			{
				if (j == screen_files_name.size() - 1)
				{
					system("cls");
					setTextColor(Color::WHITE);

					cout << "\n\n\n\n                       YOU WIN!!!!!!!!" << endl << endl;
					cout << "                      Press any key to return to the menu";
				}
			}
			else 
			{
				exit(0);
			}

		}
			
		else if (this->_state == 3)
		{
			playLoadMode(pacman, ghosts, fruit, screen_files[j]);
		}

		else if(this->_state ==4)
		{
			playLoadSilentMode(pacman, ghosts, fruit, screen_files[j]);
			system("cls");
			cout << "Test Secceeded" << endl;
		}

		//init steps is to initialize the vector
		pacman.initSteps();
		fruit.initSteps();
		for (int i = 0; i < ghosts.size(); i++)
		{
			ghosts[i].initSteps();
		}
		
		j++;
	}
}

void Game::playGame(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard)
{
	int countspeed = 0;//countspeed is a variable that responsible for the movement of the ghost and the fruit
	int timePoint = 0;

	Direction tap = Direction::STAY1;
	Direction prevtap = Direction::STAY1;

	fruit.setrandposfruit(newBoard);

	newBoard.printBoard();
	newBoard.printLivesAndScore(pacman.getlives(), pacman.getscore(), pacman.getbonus());

	for (int i = 0; i < ghosts.size(); i++) //print ghosts
	{
		ghosts[i].printObject();
	}

	if (fruit.getShow() == true) //print fruit
	{
		fruit.printObject();
	}

	pacman.printObject(); //pacman


	while (pacman.getlives() != 0 && (pacman.getscore()-firstScore) != newBoard.getTotalFood())
	{
		Sleep(200); //The speed of Pacman
		Positions prevpos(pacman.getpos());

		//if any key is hit by the user
		if (_kbhit())
		{
			tap = (Direction)_getch();

			if (tap == Direction::EXIT)
			{
				newBoard.setVectorresults(timePoint);
				newBoard.setVectorresults(2);
				CreateFileSteps(pacman, ghosts, fruit, newBoard, timePoint);
				CreateFileResult(pacman, ghosts, fruit, newBoard);
				exit(0);
			}
			if (tap == Direction::ESC)//if the tap is ESC the game in pause
			{
				newBoard.printPause();

				while (_getch() != (char)Direction::ESC) {}

				//when the tap is again ESC the pause is stopping and the pacman move according to the prev tap
				tap = prevtap;

				gotoxy(newBoard.get_livesAndScore().getX(), newBoard.get_livesAndScore().getY() + 1); //delete the line pause
				cout << "                    ";
				gotoxy(newBoard.get_livesAndScore().getX(), newBoard.get_livesAndScore().getY() + 2); //delete the line pause
				cout << "                    ";
			}
			//check if the tap is a right move for the pacman
			else if (tap == Direction::RIGHT1 || tap == Direction::RIGHT2 || tap == Direction::UP1 || tap == Direction::UP2 || tap == Direction::DOWN1 || tap == Direction::DOWN2 || tap == Direction::LEFT1 || tap == Direction::LEFT2 || tap == Direction::STAY1 || tap == Direction::STAY2)
			{
				prevtap = tap;//save the previous tap
			}
		}

		//If we don't get any key - move with the same direction
		if (pacman.move(prevtap, newBoard) == false)//check if the pacman arrived to wall, else, set pos of pacman
		{
			newBoard.printprevpos(prevpos, (char)Sign::PACMAN);
			prevtap = Direction::STAY1;
			tap = Direction::STAY1;
			pacman.setdir(tap);
		}

		//the pacman move
		if ((tap != Direction::STAY1) && (tap != Direction::STAY2))
		{
			newBoard.printprevpos(prevpos, (char)Sign::PACMAN);
		}

		//save pacman move in the file steps
		if (this->_state == 2)
		{
			pacman.setVectorSteps((int)pacman.getdir());
		}

		//print the score's pacman
		if (newBoard.getCharFromBoard(pacman.getpos()) == (char)Sign::FOOD)
		{
			pacman.addScore(1);
			newBoard.printLivesAndScore(pacman.getlives(), pacman.getscore(), pacman.getbonus());
			newBoard.changeBoard(pacman.getpos());
		}

		//pacman eats fruit
		if ((checkcollision(pacman.getpos(), fruit.getpos())) == true)
		{
			pacman.setbonus(fruit.getFruitNum());
			fruit.setShow(false);
			newBoard.printLivesAndScore(pacman.getlives(), pacman.getscore(), pacman.getbonus());
		}

		//check collision ghosts and pacman
		for (int i = 0; i < ghosts.size(); i++)
		{
			if ((checkcollision(pacman.getpos(), ghosts[i].getpos()) == true))
			{
				collisionPacmanGhost(pacman, ghosts, fruit, newBoard);
				tap = Direction::STAY1;
				prevtap = Direction::STAY1;
				countspeed = 0;
				newBoard.setVectorresults(timePoint);
			}
		}

		//the fruit move
		if (tap != Direction::ESC && countspeed % 2 == 0 && fruit.getShow() == true)
		{
			newBoard.printprevpos(fruit.getpos(), (char)fruit.getSign());
			fruit.moveRandom(newBoard);
			fruit.printObject();
		}

		//the ghost move
		if (tap != Direction::ESC && countspeed % 2 == 0)
		{
			for (int i = 0; i < ghosts.size(); i++)
			{
				newBoard.printprevpos(ghosts[i].getpos(), (char)Sign::GHOST);
				ghosts[i].ghostMove(pacman.getpos(), newBoard);
				ghosts[i].printObject();
				if (this->_state == 2)
				{
					ghosts[i].setVectorSteps((int)ghosts[i].getdir());
				}
			}
		}

		//check collision ghosts and pacman
		for (int i = 0; i < ghosts.size(); i++)
		{
			if ((checkcollision(pacman.getpos(), ghosts[i].getpos()) == true))
			{
				collisionPacmanGhost(pacman, ghosts, fruit, newBoard);
				tap = Direction::STAY1;
				prevtap = Direction::STAY1;
				countspeed = 0;
				newBoard.setVectorresults(timePoint);
			}
		}

		//pacman eats fruit
		if ((checkcollision(pacman.getpos(), fruit.getpos())) == true)
		{
			pacman.setbonus(fruit.getFruitNum());
			fruit.setShow(false);
			newBoard.printLivesAndScore(pacman.getlives(), pacman.getscore(), pacman.getbonus());
		}

		//collision ghost and fruit
		for (int i = 0; i < ghosts.size(); i++)
		{
			if (checkcollision(fruit.getpos(), ghosts[i].getpos()) == true)
			{
				newBoard.printprevpos(fruit.getpos(), (char)fruit.getSign());
				fruit.setShow(false);
			}
		}

		//every 60 sec the fruit is disapear and 60 sec later show again on the screen
		if (countspeed % 60 == 59)
		{
			if (fruit.getShow() == true)
			{
				newBoard.printprevpos(fruit.getpos(), (char)fruit.getSign());
				fruit.setShow(false);
			}
			else
			{
				fruit.setrandposfruit(newBoard);
				fruit.randFruitNum();
				fruit.setShow(true);
			}
		}

		if (this->_state == 2)
		{
			fruit.setVecShow(fruit.getShow());
			fruit.setVecValue((char)fruit.getSign());
			fruit.setVecPositions(fruit.getpos().getX(), fruit.getpos().getY());
		}

		pacman.printObject();
		countspeed++;
		timePoint++;
	}

	newBoard.setVectorresults(timePoint);

	CreateFileSteps(pacman, ghosts, fruit, newBoard, timePoint);
	CreateFileResult(pacman, ghosts, fruit, newBoard);
}

bool Game::checkcollision(const Positions& object1, const Positions& object2)
{
	if ((object1.getX() == object2.getX()) && (object1.getY() == object2.getY()))
	{
		return true;
	}

	return false;
}

void Game::collisionPacmanGhost(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard)
{
	pacman.changeLives();//the pacman lost live
	if (this->_state != 4)
	{
		newBoard.printLivesAndScore(pacman.getlives(), pacman.getscore(), pacman.getbonus());
	}

	pacman.changePacman(pacman.getlives(), pacman.getscore());

	
		for (int i = 0; i < ghosts.size(); i++)
		{
			if (this->_state != 4)
			{
				newBoard.printprevpos(ghosts[i].getpos(), (char)Sign::GHOST);
			}
			ghosts[i].changeGhost();
		}
		
		if (this->_state == 1 || this->_state == 2)
		{
			newBoard.printprevpos(fruit.getpos(), (char)fruit.getSign());
			fruit.setrandposfruit(newBoard);
			fruit.randFruitNum();
		}
	
}






void Game::CreateFileSteps(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard, int timePoint)
{
	int count = 0;
	int countGhosts = 0;

	string steps = newBoard.getnameBoard() + (".steps");
	ofstream file_steps(steps, ios_base::out);//create file for write

	while (count != pacman.getVector().size())
	{
		file_steps << pacman.getVector()[count] << " ";
		if (count % 2 == 0)
		{
			for (int i = 0; i < ghosts.size(); i++)
			{
				file_steps << ghosts[i].getVector()[countGhosts] << " ";
			}
			countGhosts++;
		}

		if (fruit.getVecShow()[count] == 1)
		{
			file_steps << fruit.getVecShow()[count] << " ";
			file_steps << fruit.getVecValue()[count] << " ";
			file_steps << fruit.getVecPositions()[count].getX() << " ";
			file_steps << fruit.getVecPositions()[count].getY() << endl;
		}
		else
			file_steps << fruit.getVecShow()[count] << endl;

		count++;
	}

	pacman.initSteps();
	fruit.initVecPositions();
	fruit.initVecShow();
	fruit.initVecValue();
	for (int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i].initSteps();
	}


	file_steps.close();
}

void Game::CreateFileResult(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard)
{
	int count = 0;
	string result = newBoard.getnameBoard() + (".result");
	ofstream file_result(result, ios_base::out);//create file for write

	while (count != newBoard.getVector().size())
	{
		file_result << newBoard.getVector()[count] << endl;
		count++;
	}

	//0-Game over, 1-pass to the next screen or win
	if (pacman.getlives() == 0)
	{
		file_result << 0 << endl;
	}
	else if((pacman.getscore() - firstScore == newBoard.getTotalFood()))
	{
		file_result << 1 << endl;
	}

	file_result.close();
}

void Game::playLoadMode(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard)
{
	LoadFileStepsVecs(pacman, ghosts, fruit, newBoard);

	int countspeed = 0;//countspeed is a variable that responsible for the movement of the ghost and the fruit
	int timePoint = 0;
	int countghost = 0;
	int countfruit = 0;


	Direction tap;

	newBoard.printBoard();
	newBoard.printLivesAndScore(pacman.getlives(), pacman.getscore(), pacman.getbonus());

	for (int i = 0; i < ghosts.size(); i++)//print ghosts
	{
		ghosts[i].printObject();
	}

	pacman.printObject();

	//while the file steps is not in the end
	for (int j = 0; j < pacman.getVector().size(); j++)
	{
		Sleep(100); //The speed of Pacman
		Positions prevpos(pacman.getpos());

		tap = (Direction)(pacman.getVector()[timePoint]);

		//the pacman move
		if ((tap != Direction::STAY1) && (tap != Direction::STAY2))
		{
			pacman.move(tap, newBoard);
			newBoard.printprevpos(prevpos, (char)Sign::PACMAN);
		}

		//print score and lives
		if (newBoard.getCharFromBoard(pacman.getpos()) == (char)Sign::FOOD)//print the score's pacman
		{
			pacman.addScore(1);
			newBoard.printLivesAndScore(pacman.getlives(), pacman.getscore(), pacman.getbonus());
			newBoard.changeBoard(pacman.getpos());
		}
		//pacman eats fruit
		if (fruit.getShow() == true)
		{
			if ((checkcollision(pacman.getpos(), fruit.getpos())) == true)
			{
				pacman.setbonus(fruit.getFruitNum());
				newBoard.printLivesAndScore(pacman.getlives(), pacman.getscore(), pacman.getbonus());
			}
		}

		//check collision ghosts and pacman
		for (int i = 0; i < ghosts.size(); i++)//ghost
		{
			if ((checkcollision(pacman.getpos(), ghosts[i].getpos()) == true))
			{
				collisionPacmanGhost(pacman, ghosts, fruit, newBoard);
				countspeed = 0;
			}
		}

		//the ghost move
		if (countspeed % 2 == 0)
		{
			for (int i = 0; i < ghosts.size(); i++)
			{
				int tempGhostTap;
				tempGhostTap = ghosts[i].getVector()[countghost];

				newBoard.printprevpos(ghosts[i].getpos(), (char)Sign::GHOST);
				ghosts[i].moveByDirInLoadMode((Direction)tempGhostTap);
				ghosts[i].printObject();
			}
			countghost++;
		}

		
		fruit.setShow(fruit.getVecShow()[timePoint]);
		//the fruit move
		if (fruit.getShow() == true )
		{
			fruit.setSign(fruit.getVecValue()[countfruit]);
			if (timePoint != 0)
			{
				newBoard.printprevpos(fruit.getpos(), (char)fruit.getSign());
			}
			fruit.setpos(fruit.getVecPositions()[countfruit].getX(), fruit.getVecPositions()[countfruit].getY());

			fruit.printObject();
			countfruit++;
		}
		else if (fruit.getShow() == false)
		{
			newBoard.printprevpos(fruit.getpos(), (char)fruit.getSign());
		}

		//check collision ghosts and pacman
		for (int i = 0; i < ghosts.size(); i++)//ghost
		{
			if ((checkcollision(pacman.getpos(), ghosts[i].getpos()) == true))
			{
				collisionPacmanGhost(pacman, ghosts, fruit, newBoard);
				countspeed = 0;
			}
		}

		//check if pacman eats fruit
		if ((checkcollision(pacman.getpos(), fruit.getpos())) == true)
		{
			pacman.setbonus(fruit.getFruitNum());
			newBoard.printLivesAndScore(pacman.getlives(), pacman.getscore(), pacman.getbonus());
		}

		//check collision ghosts and fruit
		for (int i = 0; i < ghosts.size(); i++)
		{
			if (checkcollision(fruit.getpos(), ghosts[i].getpos()) == true)
			{
				newBoard.printprevpos(fruit.getpos(), (char)fruit.getSign());
			}
		}

		pacman.printObject();
		countspeed++;
		timePoint++;
	}

	pacman.initSteps();
	fruit.initVecPositions();
	fruit.initVecShow();
	fruit.initVecValue();
	for (int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i].initSteps();
	}
}

void Game::playLoadSilentMode(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard)
{
	LoadFileStepsVecs(pacman, ghosts, fruit, newBoard);
	LoadFileResultsVecs(newBoard);

	int countspeed = 0;//countspeed is a variable that responsible for the movement of the ghost and the fruit
	int timePoint = 0;
	int countghost = 0;
	int countVecResult = 0;

	Direction tap;
	fruit.setShow(false);

	//while the file steps is not in the end
	for (int j = 0; j < pacman.getVector().size(); j++)
	{
		//Sleep(20); //The speed of Pacman

		Positions prevpos(pacman.getpos());
		tap = (Direction)(pacman.getVector()[timePoint]);

		//the pacman move
		if ((tap != Direction::STAY1) && (tap != Direction::STAY2))
		{
			pacman.move(tap, newBoard);
		}

		//print score and lives
		if (newBoard.getCharFromBoard(pacman.getpos()) == (char)Sign::FOOD)//print the score's pacman
		{
			pacman.addScore(1);
			newBoard.changeBoard(pacman.getpos());
		}

		//check collision ghosts and pacman
		for (int i = 0; i < ghosts.size(); i++)//ghost
		{
			if ((checkcollision(pacman.getpos(), ghosts[i].getpos()) == true))
			{
				collisionPacmanGhost(pacman, ghosts, fruit, newBoard);
				countspeed = 0;

				if (timePoint != newBoard.getVector()[countVecResult])
				{
					system("cls");
					cout << "Test Failed" << endl;
					exit(1);
				}
				countVecResult++;
			}
		}

		//the ghost move
		if (countspeed % 2 == 0)
		{
			for (int i = 0; i < ghosts.size(); i++)
			{
				int tempGhostTap;
				tempGhostTap = ghosts[i].getVector()[countghost];
				ghosts[i].moveByDirInLoadMode((Direction)tempGhostTap);
			}
			countghost++;
		}


		//check collision ghosts and pacman
		for (int i = 0; i < ghosts.size(); i++)//ghost
		{
			if ((checkcollision(pacman.getpos(), ghosts[i].getpos()) == true))
			{
				collisionPacmanGhost(pacman, ghosts, fruit, newBoard);
				countspeed = 0;
				if (timePoint != newBoard.getVector()[countVecResult])
				{
					system("cls");
					cout << "Test Failed" << endl;
					exit(1);
				}
				countVecResult++;
			}
		}

		countspeed++;
		timePoint++;
	}


	if (newBoard.getVector()[countVecResult] != timePoint - 1)
	{
		system("cls");
		cout << "TestFailed!" << endl;
		exit(1);
	}
	
	(countVecResult)++;

	if (newBoard.getVector()[countVecResult] == 0)
	{
		system("cls");
		cout << "Test Succeeded - GameOver!" << endl;
		exit(1);
	}
	else if (newBoard.getVector()[countVecResult] == 2)
	{
		system("cls");
		cout << "Test Succeeded - You end it in the middle of the game!" << endl;
		exit(1);
	}
	else if ((newBoard.getVector()[countVecResult] != 0) && (newBoard.getVector()[countVecResult] != 1))
	{
		system("cls");
		cout << "TestFailed!" << endl;
		exit(1);
	}

	countVecResult = 0;
	pacman.initSteps();
	fruit.initVecPositions();
	fruit.initVecShow();
	fruit.initVecValue();
	for (int i = 0; i < ghosts.size(); i++)
	{
		ghosts[i].initSteps();
	}
}

void Game::LoadFileStepsVecs(Pacman& pacman, vector<Ghost>& ghosts, Fruit& fruit, Board& newBoard)
{
	char valueFruit;
	int count = 0;
	int dirPacman, showFruit;
	int posFruitX, posFruitY;
	string steps = newBoard.getnameBoard() + (".steps");
	ifstream file_steps(steps, ios_base::in);//open file for read
	while (!(file_steps.eof()))
	{
		file_steps >> dirPacman;
		pacman.setVectorSteps(dirPacman);
		if (count % 2 == 0)
		{
			for (int i = 0; i < ghosts.size(); i++)
			{
				int dirGhost;
				file_steps >> dirGhost;
				ghosts[i].setVectorSteps(dirGhost);
			}
		}
		file_steps >> showFruit;
		fruit.setVecShow(showFruit);
		if (showFruit == 1)
		{
			file_steps >> valueFruit;
			fruit.setVecValue(valueFruit);
			file_steps >> posFruitX;
			file_steps >> posFruitY;
			fruit.setVecPositions(posFruitX, posFruitY);
		}
		count++;
	}

	file_steps.close();
}

void Game::LoadFileResultsVecs(Board& newBoard)
{
	int newResult;
	string result = newBoard.getnameBoard() + (".result");
	ifstream file_result(result, ios_base::in);//create file for write
	while (!(file_result.eof()))
	{
		file_result >> newResult;
		newBoard.setVectorresults(newResult);
	}
	file_result.close();
}

void Game::removeAllFiles()
{
	for (const auto& file : fs::directory_iterator("."))
	{

		if (file.path().extension() == (".steps")|| file.path().extension() == (".result"))
		{
			remove(file.path());
		}
	}
}