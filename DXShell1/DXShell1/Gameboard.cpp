/*
* FILENAME: Gameboard.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Gameboard
*/
#include "Gameboard.h"
#include <time.h>

//
// METHOD:Gameboard
// DESCRIPTION: Constructor
// PARAMETERS: na
// RETURNS: na
//
Gameboard::Gameboard()
{
}

//
// METHOD:~Gameboard
// DESCRIPTION:Destructor
// PARAMETERS: na
// RETURNS: na
//
Gameboard::~Gameboard() { }

//
// METHOD:GamePiecePositions
// DESCRIPTION:na
// PARAMETERS: na
// RETURNS: na
//
void Gameboard::GamePiecePositions()
{
	
}

//
// METHOD:GetGameboard
// DESCRIPTION:Accessor, returns a 2 dimentional int gameboard
// PARAMETERS: na
// RETURNS: int**
//
int** Gameboard::GetGameboard() {

	return grid;
}


//
//	METHOD: RerollBoard()
//	DESCRIPTION: This method random generates between 0 - 99,
//				 if the value is less than 5 (1/20 chance), we reroll
//				 a value between 1-3. That value is stored within the 
//			     two-dimentional aray grid.
//	PARAMETERS: void
//	RETURNS: void
//
//
void Gameboard::RerollBoard()
{
	time_t t;
	srand((unsigned)time(&t));

	grid = new int*[10];

	//clientHeight = (int)gfx->GetRenderTarget()->GetSize().height;
	//clientWidth = (int)gfx->GetRenderTarget()->GetSize().height;

	for (int i = 0; i < 10; i++) //y coordinate
	{
		grid[i] = new int[10];

		for (int j = 0; j < 10; j++) //x coordinate
		{
			dice = rand() % 100;
			if (dice < 5)
			{
				dice = rand() % 3 + 1;
				grid[i][j] = dice;
			}
		}
	}
}