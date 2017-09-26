/*
* FILENAME: Level1.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Level1
*/
#include "Level1.h"
#include "GameController.h"
#include "Graphics.h"
#include "Planet.h"
#include <cmath>
#include "Sound.h"

//
// METHOD:Load
// DESCRIPTION: Load Level one assests, including the background planets and spaceships
// PARAMETERS: N/A
// RETURNS: void
//
void Level1::Load() 
{
	soundCount = 1;

	healSound = new Sound();
	explosionSound = new Sound();
	spaeTravelSound = new Sound();

	spaceExplorationTwoSound = new Sound();
	spaceExplorationThirdSound = new Sound();
	
	spaceExplorationOneSound = new Sound();
	spaceExplorationOneSound->SoundInitialize("SpaceExplorationOne.wav");
	spaceExplorationOneSound->RunSoundFileOnce();

	//create the gameboard
	StartGame = true;
	gameBoard = new Gameboard();
	gameBoard->RerollBoard();

	//load the sector background
	userClicked = 0;
	y = 0.0f;
	y = ySpeed = 0.0f;
	sprites = new SpriteSheet(L"SectorBackground.bmp", gfx); //This is where we can specify our file system object!
	//sprites->Draw(0, 0, (int)gfx->GetRenderTarget()->GetSize().width, (int)gfx->GetRenderTarget()->GetSize().height);

	//set the gameboard to the clientwindow size
	gameBoard->setH(gfx->GetDeviceContext()->GetSize().height / 10);
	gameBoard->setW(gfx->GetDeviceContext()->GetSize().width / 10);

	//reset visted planets
	for (int i = 0; i < 100; i++)
	{
		plunderedYResource[i] = -1;
		plunderedXResource[i] = -1;
	}

	//set sector width and height
	SetSectors(gfx);

	//load planet bitmaps
	planets[0] = Planet("Planet1.bmp", gfx);
	planets[1] = Planet("Planet2.bmp", gfx);
	planets[2] = Planet("Planet3.bmp", gfx);

	//load SETEnterprise bitmap
	SETEnterprise = new Starship("ShipBase.bmp", "ShipShielded.bmp", gfx);
	//set ship cooridinates
	SETEnterprise->SetXCoordinate(0.0);
	SETEnterprise->SetYCoordinate((gfx->GetDeviceContext()->GetSize().height / 2));

	//set ship enetery and science
	SETEnterprise->SetShipEnergy(900);
	SETEnterprise->SetShipScience(0);

	//chromakey bitmap
	SETEnterprise->GetSpriteBase()->ChromaKeyEffect(
		0.0F,
		0.0F,
		gameBoard->getW(),
		gameBoard->getH(),
		1
	);

	SETEnterprise->GetSpriteDetail()->ChromaKeyEffect(
		0.0F,
		0.0F,
		gameBoard->getW(),
		gameBoard->getH(),
		1
	);

	SETEnterprise->GetShieldedSpritesheet()->ChromaKeyEffect(
		0.0F,
		0.0F,
		gameBoard->getW(),
		gameBoard->getH(),
		1
	);

	SETEnterprise->GetSprite600Health()->ChromaKeyEffect(
		0.0F,
		0.0F,
		gameBoard->getW(),
		gameBoard->getH(),
		1
	);

	SETEnterprise->GetSprite300Health()->ChromaKeyEffect(
		0.0F,
		0.0F,
		gameBoard->getW(),
		gameBoard->getH(),
		1
	);

	SETEnterprise->GetSpriteExplosion()->ChromaKeyEffect(
		0.0F,
		0.0F,
		gameBoard->getW(),
		gameBoard->getH(),
		1
	);


	//load klingon bitmap
	KlingonShip = new Starship("EnemyShip.bmp", gfx);
	//set klingon coordinates
	KlingonShip->SetXCoordinate(SETEnterprise->GetXCoordinate() + (gfx->GetDeviceContext()->GetSize().width - SectorX));
	KlingonShip->SetYCoordinate(SETEnterprise->GetYCoordinate());

	//chromakey klingonship
	KlingonShip->GetSpriteBase()->ChromaKeyEffect(
		0.0F,
		0.0F,
		gameBoard->getW(),
		gameBoard->getH(),
		0
	);

	KlingonShip->GetSpriteExplosion()->ChromaKeyEffect(
		0.0F,
		0.0F,
		gameBoard->getW(),
		gameBoard->getH(),
		1
	);

	//place planets on gameboard
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (gameBoard->GetGameboard()[i][j] >= 1 && gameBoard->GetGameboard()[i][j] <= 3)
			{
				planets[gameBoard->GetGameboard()[i][j] - 1].getSpriteSheet()->ChromaKeyEffect(
					(float)i*gameBoard->getW(),
					(float)j*gameBoard->getH(),
					(float)(gameBoard->getW() + (i*gameBoard->getW())),
					(float)(gameBoard->getH() + (j*gameBoard->getH())),
					1
				);
			}
		}
	}
}


//
// METHOD:loadStarship
// DESCRIPTION:renders the startships at there new positions
// PARAMETERS: Graphics* gfx
// RETURNS: void
//
void Level1::loadStarship(Graphics* gfx)
{
	SETEnterprise->Render(SETEnterprise->GetXCoordinate(), SETEnterprise->GetYCoordinate());
	KlingonShip->Render(KlingonShip->GetXCoordinate(), KlingonShip->GetYCoordinate(), 1);
}


//
//	METHOD: loadPlanets()
//	DESCRIPTION: This method takes the values seeded in the Gameboards grid, along with the,
//				 height and width of a single sector. With both these values it uses derived
//               coordinates to render planets objects to the ClientWindow
//				 **NOTE although this method is called loadPlanets its really used for 
//				 rendering, preloaded planet sprites are passed in a rendered.
//	PARAMETERS: Graphics* gfx
//			    SpriteSheet* sprites
//  RETURNS: VOID
//
void Level1::loadPlanets(Graphics* gfx, SpriteSheet* sprites)
{
	//gather sector width and height
	float sectorWidth = gfx->GetDeviceContext()->GetSize().width / 10;
	float sectorHeight =  gfx->GetDeviceContext()->GetSize().height / 10;

//	D2D_POINT_2F point;
	for (int i = 0; i < 10; i++) //y axis
	{
		for (int j = 0; j < 10; j++) //x axis
		{
			//check value at index to see if we have a planet we want to render
			if (gameBoard->GetGameboard()[i][j] >= 1 && gameBoard->GetGameboard()[i][j] <= 3) 
			{
				//render that planet
				planets[gameBoard->GetGameboard()[i][j]- 1].Render(i*sectorWidth, j*sectorHeight, (sectorWidth + (i*sectorWidth)), (sectorHeight + (j*sectorHeight)));
			}
		}
	}
}

//
// METHOD: unload
// DESCRIPTION: delete sprites
// PARAMETERS: n/a
// RETURNS: void
//
void Level1::Unload()
{
	delete sprites;
}


//
// METHOD: ResetShipPositions
// DESCRIPTION: dresets ship positions
// PARAMETERS: n/a
// RETURNS: void
//
void Level1::ResetShipPositions()
{
	//reset SETEnterprise
	SETEnterprise->SetXCoordinate(0.0);
	SETEnterprise->SetYCoordinate((gfx->GetDeviceContext()->GetSize().height / 2));
	SETEnterprise->GetVector()->FrameRatio(0, 0);
	SETEnterprise->SetOrientation(0);

	//Reset Klingon ship
	KlingonShip->SetXCoordinate(SETEnterprise->GetXCoordinate() + (gfx->GetDeviceContext()->GetSize().width - SectorX));
	KlingonShip->SetYCoordinate(SETEnterprise->GetYCoordinate());
	SETEnterprise->SetXDestination(SETEnterprise->GetXCoordinate());
	SETEnterprise->SetYDestination(SETEnterprise->GetYCoordinate());
	KlingonShip->SetOrientation(0);

	SETEnterprise->SetInTransit(false);

}

void Level1::ResetKlingonPosition()
{
	KlingonShip->SetXCoordinate(gfx->GetDeviceContext()->GetSize().width - SectorX);
	KlingonShip->SetYCoordinate(gfx->GetDeviceContext()->GetSize().height / 2);
	KlingonShip->SetOrientation(0);
}


//
// METHOD:ResetGameBoard
// DESCRIPTION:Resets plundered planets and gameboard
// PARAMETERS: na
// RETURNS: na
//
void Level1::ResetGameBoard()
{
	for (int i = 0; i < 100; i++)
	{
		plunderedYResource[i] = -1;
		plunderedXResource[i] = -1;
	}

	gameBoard->RerollBoard();
	for (int i = 0; i < 10; i++) //y coordinate
	{
		for (int j = 0; j < 10; j++) //x coordinate
		{
			//set chromakey and scaling effects to planets
			if (gameBoard->GetGameboard()[i][j] >= 1 && gameBoard->GetGameboard()[i][j] <= 3)
			{
				planets[gameBoard->GetGameboard()[i][j] - 1].getSpriteSheet()->ChromaKeyEffect(
					(float)i*gameBoard->getW(),
					(float)j*gameBoard->getH(),
					(float)(gameBoard->getW() + (i*gameBoard->getW())),
					(float)(gameBoard->getH() + (j*gameBoard->getH())),
					1
				);
			}
		}
	}
}


//
// METHOD:UpdateEnterpriseDestination
// DESCRIPTION: updates the enterprises destination
// PARAMETERS:double xCoordinate, double yCoordinate
// RETURNS: void
//
void Level1::UpdateEnterpriseDestination(double xCoordinate, double yCoordinate)
{
	//set an x and y destination
	SETEnterprise->SetXDestination(xCoordinate - (SectorX / 2));
	SETEnterprise->SetYDestination(yCoordinate - (SectorY / 2));

	// get the x,y distance
	SETEnterprise->GetVector()->XVectorLength(SETEnterprise->GetXDestination(), SETEnterprise->GetXCoordinate());
	SETEnterprise->GetVector()->YVectorLength(SETEnterprise->GetYDestination(), SETEnterprise->GetYCoordinate());
	// get the movement ratio
	SETEnterprise->GetVector()->FrameRatio(SETEnterprise->GetVector()->GetXLength(), SETEnterprise->GetVector()->GetYLength());

	SETEnterprise->SetOrientation();

	//set our ship to in transit mode
	SETEnterprise->SetInTransit(true);

}

//
// METHOD:UpdateEnterprisePosition
// DESCRIPTION:update enterprises positons
// PARAMETERS: na
// RETURNS: void
//
void Level1::UpdateEnterprisePosition()
{
	SETEnterprise->SetXCoordinate(SETEnterprise->GetXCoordinate() + (SETEnterprise->GetVector()->GetXRatio() * 5));
	SETEnterprise->SetYCoordinate(SETEnterprise->GetYCoordinate() + (SETEnterprise->GetVector()->GetYRatio() * 5));
}

//
// METHOD:UpdateKlingonDestination
// DESCRIPTION: updates kingons destination based on enterprises position
// PARAMETERS: na
// RETURNS: void
//
void Level1::UpdateKlingonDestination()
{
	KlingonShip->SetXDestination(SETEnterprise->GetXCoordinate());
	KlingonShip->SetYDestination(SETEnterprise->GetYCoordinate());
	KlingonShip->GetVector()->XVectorLength(SETEnterprise->GetXCoordinate(), KlingonShip->GetXCoordinate());
	KlingonShip->GetVector()->YVectorLength(SETEnterprise->GetYCoordinate(), KlingonShip->GetYCoordinate());
	// get the movement ratio
	KlingonShip->GetVector()->FrameRatio(KlingonShip->GetVector()->GetXLength(), KlingonShip->GetVector()->GetYLength());

	KlingonShip->SetOrientation();
}

//
// METHOD: UpdateKlingonPosition
// DESCRIPTION: update klingon ships position on gameboard
// PARAMETERS: na
// RETURNS: void
//
void Level1::UpdateKlingonPosition()
{
	if (KlingonShip->GetVector()->GetMagnitude() <= ((gfx->GetDeviceContext()->GetSize().width / 20)*4) ||
		KlingonShip->GetVector()->GetMagnitude() <= ((gfx->GetDeviceContext()->GetSize().height / 20) * 4))
	{
		KlingonShip->SetXCoordinate(KlingonShip->GetXCoordinate() + (KlingonShip->GetVector()->GetXRatio() * 5.15));
		KlingonShip->SetYCoordinate(KlingonShip->GetYCoordinate() + (KlingonShip->GetVector()->GetYRatio() * 5.15));
	}
	else
	{
		KlingonShip->SetXCoordinate(KlingonShip->GetXCoordinate() + (KlingonShip->GetVector()->GetXRatio() * 4));
		KlingonShip->SetYCoordinate(KlingonShip->GetYCoordinate() + (KlingonShip->GetVector()->GetYRatio() * 4));
	}
}

//
// METHOD:CheckTurnIsFinshed
// DESCRIPTION:checks to see if the Enterprise has reached its destination or is still in transit
// PARAMETERS: na
// RETURNS: void
//
void Level1::CheckTurnIsFinshed()
{
	if (fabs(SETEnterprise->GetXCoordinate() - SETEnterprise->GetXDestination()) < 6 &&
		fabs(SETEnterprise->GetYCoordinate() - SETEnterprise->GetYDestination()) < 6)
	{
		SETEnterprise->SetXCoordinate(SETEnterprise->GetXDestination());
		SETEnterprise->SetYCoordinate(SETEnterprise->GetYDestination());

		KlingonShip->SetOrientation();

		SETEnterprise->SetInTransit(false);
		userClicked = 0;
	}
}

//
// METHOD: PlanetCollisionDetection
// DESCRIPTION: detects if enterprise passes over a planet
// PARAMETERS: na
// RETURNS: void
//
void Level1::PlanetCollisionDetection()
{
	time_t t;
	srand((unsigned)time(&t));
	//calculate which sector enterprise is in
	SETEnterprise->CalculateSectorPosition(gfx->GetDeviceContext()->GetSize().width, gfx->GetDeviceContext()->GetSize().height);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if ((SETEnterprise->GetSectorPositionX() <= i*(gfx->GetDeviceContext()->GetSize().width/20)) ||
				(SETEnterprise->GetSectorPositionY() <= j*(gfx->GetDeviceContext()->GetSize().height / 20)))
			{
				if (SETEnterprise->GetSectorPositionX() == i && SETEnterprise->GetSectorPositionY() == j)
				{
					//check if a planet exists within this sector enterprise is currently in
					switch (gameBoard->GetGameboard()[i][j])
					{
					case 1: //case earth
						if (plunderedXResource[i] == -1 || plunderedYResource[j] == -1)
						{
							healSound->SoundInitialize("Heal.wav");
							healSound->RunSoundFileOnce();

							plunderedXResource[i] = i;
							plunderedYResource[j] = j;

							int energy = rand() % 300;
							int science = rand() % 300;

							SETEnterprise->SetShipEnergy(energy);
							SETEnterprise->SetShipScience(science);
							//generate health and science, assign it to SETEnterprise.
						}
						break;

					case 2: //case mars
						
						if (plunderedXResource[i] == -1 || plunderedYResource[j] == -1)
						{
							healSound->SoundInitialize("Heal.wav");
							healSound->RunSoundFileOnce();

							plunderedXResource[i] = i;
							plunderedYResource[j] = j;

							int energy = rand() % 300;
							int science = rand() % 300;

							SETEnterprise->SetShipEnergy(energy);
							SETEnterprise->SetShipScience(science);
							//generate health and science, assign it to SETEnterprise.
						}

						break;

					case 3: //case saturn

						if (plunderedXResource[i] == -1 || plunderedYResource[j] == -1)
						{
							healSound->SoundInitialize("Heal.wav");
							healSound->RunSoundFileOnce();

							plunderedXResource[i] = i;
							plunderedYResource[j] = j;

							int energy = rand() % 300;
							int science = rand() % 300;

							SETEnterprise->SetShipEnergy(energy);
							SETEnterprise->SetShipScience(science);
							//generate health and science, assign it to SETEnterprise.
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}
}


//
// METHOD: ShipCollisionDetection
// DESCRIPTION: checks to see if klingon collided with the enterprise
// PARAMETERS: na
// RETURNS: void
//
bool Level1::ShipCollisionDetection()
{
	bool resetKlingon = false;
	bool resetEverthing = false;
	bool gameOver = false;
	if (KlingonShip->GetVector()->GetMagnitude() <= (gfx->GetDeviceContext()->GetSize().width / 20) ||
		KlingonShip->GetVector()->GetMagnitude() <= (gfx->GetDeviceContext()->GetSize().height / 20))
	{
		if (!KlingonShip->getExplodeShip())
		{
			explosionSound->SoundInitialize("Explosion.wav");
			explosionSound->RunSoundFileOnce();

			KlingonShip->setExplodeShip(true);
			KlingonShip->setCollisionDetection(true);
			//minus health from SETEnterprise
			//check if it reaches zero
			//here we will check existing shield and health,
			//hopefully to help determine which bitmaps to render via flags? probably
			if (!SETEnterprise->GetEnergyShield())
			{
				SETEnterprise->SetShipEnergy(-300);
				if (SETEnterprise->GetShipEnergy() <= 0)
				{
					gameOver = true;
				}
			}
		}
	}
	return gameOver;
}
//END OF METHODS HANDLING LEVEL UPDATE


//
// METHOD: Update
// DESCRIPTION: Level1 Update method
// PARAMETERS: double xCoordinate, double yCoordinate, HWND windowHandle
// RETURNS: void
//
bool Level1::Update(double xCoordinate, double yCoordinate, HWND windowHandle)
{
	bool gameOver = false;

	this->windowHandle = windowHandle;
	//compare ships draw vector to the border of the client window
	if (SETEnterprise->GetXCoordinate() + SectorX >= gfx->GetDeviceContext()->GetSize().width)
	{
		spaeTravelSound->SoundInitialize("SpaceTravel.wav");
		spaeTravelSound->RunSoundFileOnce();

		if (soundCount == 1)
		{
			spaceExplorationOneSound->StopSoundFile();
			spaceExplorationTwoSound->SoundInitialize("SpaceExplorationTwo.wav", true);
			spaceExplorationTwoSound->RunSoundFileOnce();
			soundCount = 2;
		}
		else if (soundCount == 2)
		{
			spaceExplorationTwoSound->StopSoundFile();
			spaceExplorationThirdSound->SoundInitialize("SpaceExplorationThree.wav", true);
			spaceExplorationThirdSound->RunSoundFileOnce();
			soundCount = 3;
		}
		else
		{
			spaceExplorationThirdSound->StopSoundFile();
			spaceExplorationOneSound->SoundInitialize("SpaceExplorationOne.wav", true);
			spaceExplorationOneSound->RunSoundFileOnce();
			soundCount = 1;
		}

		ResetShipPositions();
		//reroll the board
		ResetGameBoard();
	}
	else  // if not at the border
	{
		if (!KlingonShip->getExplodeShip())
		{
			if (xCoordinate >= 0 && yCoordinate >= 0 && !(SETEnterprise->GetInTransit()))
			{
				//update enterprise destination
				UpdateEnterpriseDestination(xCoordinate, yCoordinate);
			}
			else if (SETEnterprise->GetInTransit()) //if in transit
			{

				// move the ship by ratio
				UpdateEnterprisePosition(); //update enterprise position
				PlanetCollisionDetection(); //check for planet collision

				if (SETEnterprise->GetInTransit()) //if in transit
				{
					UpdateKlingonDestination(); //update klingon destination
					UpdateKlingonPosition(); //update klingon position
					gameOver = ShipCollisionDetection(); //check for enterprise collision
				}
				CheckTurnIsFinshed();
			}
		}
		else
		{
			if (KlingonShip->getExplodeShip())
			{
				if (renderTime >= 50)
				{
					KlingonShip->setExplodeShip(false);
					renderTime = 0;
					KlingonShip->setCollisionDetection(false);
					SETEnterprise->SetEnergyShield(false);
					if (!SETEnterprise->GetEnergyShield())
					{
						ResetGameBoard();
						ResetShipPositions();
					}
					else
					{
						ResetKlingonPosition();
					}
				}
				renderTime++;
			}
		}
	}
	return gameOver;
}

//
// METHOD: Render
// DESCRIPTION: render game objects to the screen
// PARAMETERS: na 
// RETURNS: void
//
void Level1::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	sprites->Draw();
	//gameBoard = new Gameboard();
	loadPlanets(gfx, sprites);
	loadStarship(gfx);

	int height = (int)gfx->GetDeviceContext()->GetSize().height;
	int width = (int)gfx->GetDeviceContext()->GetSize().width;
}

//
// METHOD: DrawGridLines
// DESCRIPTION: Method not used
// PARAMETERS: na
// RETURNS: void
//
//void Level1::DrawGridLines()
//{
//	ID2D1SolidColorBrush* brush;
//	float sectorWidth = gfx->GetDeviceContext()->GetSize().width /10;
//	float sectorHeight = gfx->GetDeviceContext()->GetSize().height/ 10;
//
//	gfx->GetDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);
//
//	brush->SetColor(D2D1::ColorF(255.0f, 255.0f, 255.0f));
//
//	for (int i = 0; i < 10; i++)
//	{
//		gfx->GetDeviceContext()->DrawLine(
//			D2D1::Point2F((sectorWidth * i), 0),
//			D2D1::Point2F((sectorWidth * i), (gfx->GetDeviceContext()->GetSize().height)),
//			brush,
//			1.0f,
//			NULL
//		);
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		gfx->GetDeviceContext()->DrawLine(
//			D2D1::Point2F(0, sectorHeight * i),
//			D2D1::Point2F(gfx->GetDeviceContext()->GetSize().width, sectorHeight * i),
//			brush,
//			1.0f,
//			NULL
//		);
//	}
//}

//
// METHOD: SetSectors
// DESCRIPTION: sets the sector width and height
// PARAMETERS: Graphics* gfx
// RETURNS: void
//
void Level1::SetSectors(Graphics* gfx)
{
	SectorX = gfx->GetDeviceContext()->GetSize().width / 10;
	SectorY = gfx->GetDeviceContext()->GetSize().height / 10;
}