
/*
* FILENAME: Gameboard.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Gameboard
*/
#pragma once

#include "Graphics.h"



//
//	Class: Gameboard
//  Description: This class as an abstract representation of a gameboard.
//				 although gameobjects are not rendered or stored into it, acts
//				 as a way to map gameobjects out onto the ClientWindow
//
class Gameboard
{

	 int** grid;
	 float w;
	 float h;
	 int dice;

public:
	Gameboard();

	~Gameboard();
	
	void GamePiecePositions();

	int** GetGameboard();

	float getW() { return w; }
	float getH() { return h; }
	void setW(float W) { w = W; }
	void setH(float H) { h = H; }
	void RerollBoard();
};

