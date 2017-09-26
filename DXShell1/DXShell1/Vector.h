/*
* FILENAME: Vector.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Vector
*/

#pragma once
#include <iostream>

//
//	Class: Vector
//  Description: This is a helper class with transformations done on gameobjects.
//
class Vector
{
private:
	double yVectorLength;
	double xVectorLength;

	double xRatio;
	double yRatio;


	double vectorMagnitude;
	double scaledMagnitude;

public:
	// Scrub gitGood(int noobLevel);
	void XVectorLength(double a, double b);
	void YVectorLength(double a, double b);
	void VectorMagnitude(double xVector, double yVector);
	void ScaleMagnitude(double scaleFactor);
	double GetYLength();
	double GetXLength();
	double GetYRatio();
	double GetXRatio();
	double GetMagnitude();
	double GetScaledMagnitude();
	void FrameRatio(double xVector, double yVector);
};
