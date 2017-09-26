/*
* FILENAME: Level1.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Level1
*/
#pragma once
#include "GameLevel.h"
#include "Gameboard.h"
#include "Planet.h"
#include "Starship.h"
#include <time.h>
#include "Sound.h"

enum gamePieces { space = 0, earth, saturn, mars, SET_Enterprise };

//
//	Class: Level1
//  Description: This class is derived from GameLevel. The majority of
//				 SET Trek's Updating and Rendering logic is within this class
//
class Level1 : public GameLevel
{
	float y;
	float ySpeed;
	float SectorX;
	float SectorY;
    Gameboard* gameBoard;
	SpriteSheet* sprites;
	Planet planets[3];
	Starship* SETEnterprise;
	Starship* KlingonShip;
	bool StartGame;
	int userClicked;

	int renderTime = 0;

	bool withShields = false;
	bool withoutShield = false;

	Sound* healSound;
	Sound* explosionSound;
	Sound* spaeTravelSound;
	Sound* spaceExplorationOneSound;
	Sound* spaceExplorationTwoSound;
	Sound* spaceExplorationThirdSound;
	int soundCount = 0;

	int plunderedXResource[100];
	int plunderedYResource[100];

	HWND windowHandle;

public:
	void Load() override;
	void Unload() override;
	bool Update(double xCoordinate, double yCoordinate, HWND windowHandle) override;
	void Render() override;
	void loadPlanets(Graphics* gfx, SpriteSheet* sprites);
	//void DrawGridLines();
	void loadStarship(Graphics* gfx);
	void SetSectors(Graphics* gfx);


	void ResetShipPositions();
	void ResetKlingonPosition();
	void ResetGameBoard();
	void UpdateEnterpriseDestination(double xCoordinate, double yCoordinate);
	void UpdateKlingonDestination();
	void UpdateEnterprisePosition();
	void UpdateKlingonPosition();
	void CheckTurnIsFinshed();

	bool ShipCollisionDetection();
	void PlanetCollisionDetection();
};
