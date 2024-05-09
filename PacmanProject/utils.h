#pragma once
#include <iostream>
#include <istream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <process.h>
#include <ctime>
#include <vector>
#include <filesystem>
#include <string>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

enum class Direction
{
	UP1 = 87,     // Up Arrow
	UP2 = 119,    // Up Arrow 
	DOWN1 = 88,   // Down Arrow 
	DOWN2 = 120,  // Down Arrow
	LEFT1 = 65,   // Left Arrow 
	LEFT2 = 97,   // Left Arrow 
	RIGHT1 = 68,  // Right Arrow
	RIGHT2 = 100, // Right Arrow
	STAY1 = 83,   // Stay Arrow
	STAY2 = 115,  // Stay Arrow
	ESC = 27,     // Escape Key for Pause
	EXIT = 'g'    // Exit from the game back to the menu
};

enum class Color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

enum class Sign
{
	FOOD = '.',
	WALL = '#',
	TUNNEL = '^',
	SPACE = ' ',
	PACMAN = '@',
	GHOST = '$',
	Fruit5 = '5',
	Fruit6= '6',
	Fruit7 = '7',
	Fruit8 = '8',
	Fruit9 = '9',
	GAME_INFO='!'

};

enum class LEVEL
{
	BEST = '1',
	GOOD = '2',
	NOVICE = '3'
};

void setTextColor(Color colorToSet);
void gotoxy(int x, int y);
void hideCursor();
