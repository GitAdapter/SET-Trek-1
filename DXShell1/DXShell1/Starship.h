/*
* FILENAME: Starship.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Starship
*/
#pragma once

#include "GameObject.h"

//
//	Class: Starship
//  Description: This class as an abstract representation of a Starship.
//
class Starship : public GameObject
{
	Vector *shipVector;

	float shipOrientation;

	float xCoordinate;
	float yCoordinate;

	double xDestination;
	double yDestination;

	bool inTransit;
	bool firstMove;

	int sectorPositionX;
	int sectorPositionY;

	int shipEnergy;
	int shipScience;

	bool energyShield;
	bool explodeShip;
	bool collisionDetected;

	int drawTime;

	//float pursuitDistance;
	//float collisionDistance;

	wstring bitmapBase;
	wstring bitmapDetail;
	wstring bitmapShielded;
	wstring bitmap600Health;
	wstring bitmap300Health;

	SpriteSheet* spriteBase;
	SpriteSheet* spriteDetail;
	SpriteSheet* spriteShielded;
	SpriteSheet* sprite600Health;
	SpriteSheet* sprite300Health;
	SpriteSheet* spriteExplosion;

public:
	Starship();
	Starship(string whichBitmapOne, string whichBimapTwo, Graphics* gfx);
	Starship(string BitmapOne, Graphics* gfx);
	~Starship();
	void Load() override;
	void Load(int flag) override;
	void Unload() override;
	void Update() override;
	void Render() override;
	void Render(float xOneCoordinate, float yOneCoordinate);
	void Render(float xOneCoordinate, float yOneCoordinate, int flag);

	void ResetPosition();

	Vector* GetVector();

	bool getExplodeShip();
	void setExplodeShip(bool explodeShip);

	bool getCollisionDetection();
	void setCollisionDetection(bool collisionDetection);

	float GetOrientation();
	void SetOrientation();
	void SetOrientation(float orientation);

	double GetXDestination();
	double GetYDestination();

	void SetXDestination(double x);
	void SetYDestination(double y);

	float GetXCoordinate();
	float GetYCoordinate();

	void SetXCoordinate(float x);
	void SetYCoordinate(float y);

	bool GetInTransit();
	void SetInTransit(bool inTransit);

	int GetSectorPositionX();
	int GetSectorPositionY();

	void CalculateSectorPosition(float sectorXLength, float sectorYLength);
	
	int GetShipEnergy();
	void SetShipEnergy(int energy);

	int GetShipScience();
	void SetShipScience(int science);

	bool GetEnergyShield();
	void SetEnergyShield(bool energyShield);


	SpriteSheet* GetShieldedSpritesheet();

	SpriteSheet* GetSpriteBase();

	SpriteSheet* GetSpriteDetail();

	SpriteSheet* GetSpriteExplosion();

	//wstring getBitMapDetail();
	void setBitMapDetail(string bitmapName);

	SpriteSheet* GetSprite600Health();

	SpriteSheet* GetSprite300Health();

//
};