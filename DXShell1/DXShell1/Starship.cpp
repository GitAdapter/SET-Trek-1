/*
* FILENAME: Starship.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Starship
*/
#include "Starship.h"

//
// METHOD:Starship
// DESCRIPTION: Constructor
// PARAMETERS:N/A
// RETURNS:N/A
//
Starship::Starship() { }

//
// METHOD:Starship
// DESCRIPTION: COnstructor
// PARAMETERS: string whichBitmapOne, string whichBitmapTwo, Graphics* gfx
// RETURNS: N/A
//
Starship::Starship(string whichBitmapOne, string whichBitmapTwo, Graphics* gfx)
{
	explodeShip = false;
	energyShield = true;
	xCoordinate = 0.0;
	yCoordinate = 0.0;
	shipEnergy = 0;
	shipScience = 0;
	inTransit = false;
	firstMove = true;
	
	shipVector = new Vector();

	string bitmapBuffer = whichBitmapOne;
	wstring bitmapNameBase(bitmapBuffer.begin(), bitmapBuffer.end());
	bitmapBase = bitmapNameBase;

	bitmapBuffer = "ShipDetail.bmp";
	wstring bitmapNameDetail(bitmapBuffer.begin(), bitmapBuffer.end());
	bitmapDetail = bitmapNameDetail;

	bitmapBuffer = whichBitmapTwo;
	wstring bitmapNameShielded(bitmapBuffer.begin(), bitmapBuffer.end());
	bitmapShielded = bitmapNameShielded;

	bitmapBuffer = "sprite600Health.bmp";
	wstring bitmapName600Health(bitmapBuffer.begin(), bitmapBuffer.end());
	bitmap600Health = bitmapName600Health;

	bitmapBuffer = "sprite300Health.bmp";
	wstring bitmapName300Health(bitmapBuffer.begin(), bitmapBuffer.end());
	bitmap300Health = bitmapName300Health;

	this->gfx = gfx;
	Load();
}

//
// METHOD:Starship
// DESCRIPTION: Constructor
// PARAMETERS: (string whichBitmapOne, Graphics* gfx)
// RETURNS: N/A
//
Starship::Starship(string whichBitmapOne, Graphics* gfx)
{
	drawTime = 0;
	collisionDetected = false;
	explodeShip = false;
	xCoordinate = 0.0;
	yCoordinate = 0.0;
	shipEnergy = 0;
	shipScience = 0;
	inTransit = false;
	firstMove = true;

	shipVector = new Vector();

	string bitmapBuffer = whichBitmapOne;
	wstring bitmapNameBase(bitmapBuffer.begin(), bitmapBuffer.end());
	bitmapBase = bitmapNameBase;

	this->gfx = gfx;
	Load(1);
}

//
// METHOD:~Starship
// DESCRIPTION: Destructor
// PARAMETERS: N/A
// RETURNS: n/A
//
Starship::~Starship()
{

}

//
// METHOD:Load
// DESCRIPTION: load spritsheets
// PARAMETERS: N/A
// RETURNS: N/A
//
void Starship::Load()
{
	spriteBase = new SpriteSheet(L"ShipBase.bmp", gfx);
	spriteDetail = new SpriteSheet(L"ShipDetail.bmp", gfx);
	spriteShielded = new SpriteSheet(L"ShipShielded.bmp", gfx);
	sprite600Health = new SpriteSheet(L"sprite600Health.bmp", gfx);
	sprite300Health = new SpriteSheet(L"sprite300Health.bmp", gfx);
	spriteExplosion = new SpriteSheet(L"explosion.bmp", gfx);
}

//
// METHOD:Load
// DESCRIPTION: load spritesheet
// PARAMETERS: int flag
// RETURNS: void
//
void Starship::Load(int flag)
{
	spriteBase = new SpriteSheet((wchar_t*)bitmapBase.c_str(), gfx);
	spriteExplosion = new  SpriteSheet(L"explosion.bmp", gfx);
	//spriteDetail = new SpriteSheet((wchar_t*)bitmapDetail.c_str(), gfx);
}

//
// METHOD:Unload
// DESCRIPTION: unload
// PARAMETERS: void
// RETURNS: void
//
void Starship::Unload()
{
}

//
// METHOD:Update
// DESCRIPTION: update
// PARAMETERS: void
// RETURNS: void 
//
void Starship::Update()
{

}

//
// METHOD:Render
// DESCRIPTION: render
// PARAMETERS: n/a
// RETURNS: n/a
//
void Starship::Render()
{

}

//
// METHOD:Render
// DESCRIPTION: float xOneCoordinate, float yOneCoordinate
// PARAMETERS: draw ship
// RETURNS: na
//
void Starship::Render(float xOneCoordinate, float yOneCoordinate)
{
	if (shipEnergy >= 900)
	{
		if (energyShield)
		{
			spriteBase->Draw(xOneCoordinate, yOneCoordinate, shipOrientation);
			spriteShielded->Draw(xOneCoordinate, yOneCoordinate, shipOrientation);
		}
		else
		{
			spriteBase->Draw(xOneCoordinate, yOneCoordinate, shipOrientation);
		}
	}
	else if (shipEnergy > 600 && shipEnergy < 900)
	{
		spriteBase->Draw(xOneCoordinate, yOneCoordinate, shipOrientation);
	}
	else if (shipEnergy > 300 && shipEnergy <= 600)
	{
		sprite600Health->Draw(xOneCoordinate, yOneCoordinate, shipOrientation);
	}
	else if (shipEnergy <= 300)
	{
		sprite300Health->Draw(xOneCoordinate, yOneCoordinate, shipOrientation);
	}
	else if(shipEnergy <= 0)
	{
		spriteExplosion->Draw(xOneCoordinate, yOneCoordinate, shipOrientation);
		Sleep(2000);
	}
}

//
// METHOD:Render
// DESCRIPTION: draw ship
// PARAMETERS:float xOneCoordinate, float yOneCoordinate, int flag
// RETURNS:void
//
void Starship::Render(float xOneCoordinate, float yOneCoordinate, int flag)
{
	if (collisionDetected)
	{
		spriteExplosion->Draw(xOneCoordinate, yOneCoordinate, shipOrientation);
		//Sleep(2000);
		//if (drawTime >= 50)
		//{
			//ResetPosition();
			//collisionDetected = false;
			//drawTime = 0;
		//}
	//	drawTime++;
	}
	else if(!collisionDetected)
	{

		spriteBase->Draw(xOneCoordinate, yOneCoordinate, shipOrientation);
	}
}

bool Starship::getCollisionDetection()
{
	return collisionDetected;
}

void Starship::setCollisionDetection(bool collisionDetection)
{
	this->collisionDetected = collisionDetection;
}


bool Starship::getExplodeShip()
{
	return explodeShip;
}

void Starship::setExplodeShip(bool explodeShip)
{
	this->explodeShip = explodeShip;
}

void Starship::ResetPosition()
{
	SetXCoordinate(gfx->GetDeviceContext()->GetSize().width - (gfx->GetDeviceContext()->GetSize().width / 10));
	SetYCoordinate(gfx->GetDeviceContext()->GetSize().height / 2);
	SetOrientation(0);
}



//
// METHOD:GetOrientation
// DESCRIPTION: Accessor
// PARAMETERS: na
// RETURNS:float
//
float Starship::GetOrientation()
{
	return shipOrientation;
}

//
// METHOD:SetOrientation
// DESCRIPTION: Mutator
// PARAMETERS: void
// RETURNS:void
//
void Starship::SetOrientation()
{
	const float PI = 3.14159265;
	shipOrientation = atan2(yDestination - yCoordinate, xDestination - xCoordinate) * (180 / PI);
}

//
// METHOD:SetOrientation
// DESCRIPTION:Mutator
// PARAMETERS:
// RETURNS:void
//
void Starship::SetOrientation(float orientation)
{
	const float PI = 3.14159265;

	shipOrientation = 0;
}

//
// METHOD:GetVector
// DESCRIPTION:Accessor
// PARAMETERS:na
// RETURNS:Vector
//
Vector* Starship::GetVector() 
{
	return shipVector;
}

//
// METHOD:GetXCoordinate
// DESCRIPTION:Accessor
// PARAMETERS:na
// RETURNS:float
//
float Starship::GetXCoordinate()
{
	return xCoordinate;
}

//
// METHOD:GetYCoordinate
// DESCRIPTION:Accessor
// PARAMETERS:na
// RETURNS:float
//
float Starship::GetYCoordinate()
{
	return yCoordinate;
}

//
// METHOD:SetXCoordinate
// DESCRIPTION:Mutator
// PARAMETERS:float x
// RETURNS:void
//
void Starship::SetXCoordinate(float x)
{
	xCoordinate = x;
}

//
// METHOD:GetInTransit
// DESCRIPTION:Mutator
// PARAMETERS: float y
// RETURNS:na
//
void Starship::SetYCoordinate(float y)
{
	yCoordinate = y;
}

//
// METHODGetInTransit
// DESCRIPTION:Accessor
// PARAMETERS:na
// RETURNS: bool
//
bool Starship::GetInTransit()
{
	return inTransit;
}

//
// METHOD:SetInTransit
// DESCRIPTION:Mutator
// PARAMETERS:bool inTransit
// RETURNS: void
//
void Starship::SetInTransit(bool inTransit)
{
	this->inTransit = inTransit;
}

//
// METHOD:GetXDestination
// DESCRIPTION:Accessor
// PARAMETERS:void
// RETURNS:double
//
double Starship::GetXDestination()
{
	return xDestination;
}

//
// METHOD:GetYDestination
// DESCRIPTION:Accessor
// PARAMETERS:na
// RETURNS:double
//
double Starship::GetYDestination()
{
	return yDestination;
}

//
// METHOD:SetXDestination
// DESCRIPTION:Mutator
// PARAMETERS:double x
// RETURNS: void
//
void Starship::SetXDestination(double x)
{
	xDestination = x;
}

//
// METHOD:SetYDestination
// DESCRIPTION:Mutator
// PARAMETERS:double y
// RETURNS: void
//
void Starship::SetYDestination(double y)
{
	yDestination = y;
}

//
// METHOD:GetSectorPositionX
// DESCRIPTION:Accessor
// PARAMETERS: na
// RETURNS: int
//
int Starship::GetSectorPositionX()
{
	return sectorPositionX;
}

//
// METHOD:GetSectorPositionY
// DESCRIPTION:Accessor
// PARAMETERS: na
// RETURNS: int
//
int Starship::GetSectorPositionY()
{
	return sectorPositionY;
}

//
// METHOD:CalculateSectorPosition
// DESCRIPTION: Calculate the Sector position a ship is in
// PARAMETERS: float sectorXLength, float sectorYLength
// RETURNS: void
//
void Starship::CalculateSectorPosition(float sectorXLength, float sectorYLength)
{
	sectorPositionX = ((xCoordinate + (sectorXLength/50)) / (sectorXLength)) * 10;
	sectorPositionY = ((yCoordinate + (sectorXLength/50)) / (sectorYLength)) * 10;
}

//
// METHOD:GetShipEnergy
// DESCRIPTION:Accessor
// PARAMETERS: na
// RETURNS: int
//
int Starship::GetShipEnergy()
{
	return shipEnergy;
}
//
// METHOD:SetShipEnergy
// DESCRIPTION:Mutator
// PARAMETERS: int energy
// RETURNS: na
//

void Starship::SetShipEnergy(int energy)
{
	
	shipEnergy += energy;
	if (shipEnergy >= 900)
	{
		shipEnergy = 900;
		energyShield = true;
	}
}

//
// METHOD:GetShipScience
// DESCRIPTION: Accessor
// PARAMETERS: na
// RETURNS: int
//
int Starship::GetShipScience()
{
	return shipScience;
}

//
// METHOD:SetShipScience
// DESCRIPTION:Mutator
// PARAMETERS: int science
// RETURNS: void
//
void Starship::SetShipScience(int science)
{
	shipScience += science;
}


bool Starship::GetEnergyShield()
{
	return energyShield;
}


void Starship::SetEnergyShield(bool energyShield)
{
	this->energyShield = energyShield;
}


SpriteSheet* Starship::GetSpriteBase()
{
	return spriteBase;
}

SpriteSheet* Starship::GetSpriteDetail()
{
	return spriteDetail;
}


SpriteSheet* Starship::GetShieldedSpritesheet()
{
	return spriteShielded;
}

SpriteSheet* Starship::GetSprite600Health()
{
	return sprite600Health;
}

SpriteSheet* Starship::GetSprite300Health()
{
	return sprite300Health;
}

SpriteSheet* Starship::GetSpriteExplosion()
{
	return spriteExplosion;
}
//WILL NEED OTHER BITMAPS