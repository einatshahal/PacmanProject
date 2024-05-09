#include "game.h"
#include "main.h"
#include "utils.h"

/*____________________________________________________________________________
							 Pacman Project

  information: The program is about Pacman game.

			   **The board is currently formatted to 24 * 80

______________________________________________________________________________
				Names : Bar Solomon |  Einat Shahal
				ID :    314882432   |  315839431
______________________________________________________________________________*/


int main(int argc, char** argv)
{
	vector <string> state;
	Game game;

	for (int i = 0; i < argc; i++)
	{
		state.push_back(argv[i]);
	}

	if (argc == 1)
	{
		//pacman.exe
		game.setState(1);
	}
	else if (cmdOptionExists("-load-silent", state) == true)
	{
		game.setState(4);
	}
	else if (cmdOptionExists("-load", state) == true)
	{
		game.setState(3);
	}
	else if (cmdOptionExists("-save", state) == true)
	{
		game.setState(2);
	}
	game.Run();
}

bool cmdOptionExists(string state1, vector <string> &state)
{
	size_t n;
	n = state[1].find(state1);

	if (n == -1)
	{
		return false;
	}
	else 
	{
		return true;
	}
}