/*
* FILENAME: Vector.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Vector
*/

#include "Vector.h"

//
// METHOD:XVectorLength
// DESCRIPTION: calculate difference of xDestinationa and xPosition
// PARAMETERS: double a, double b
// RETURNS: na
//
void Vector::XVectorLength(double a, double b)
{
	xVectorLength = a - b;
}

//
// METHOD:YVectorLength
// DESCRIPTION: calculate difference of yDestinationa and yPosition
// PARAMETERS:double a, double b
// RETURNS: na
//
void Vector::YVectorLength(double a, double b)
{
	yVectorLength = a - b;
}

//
// METHOD:VectorMagnitude
// DESCRIPTION:calculate a vectors magnitude
// PARAMETERS:double xVector, double yVector
// RETURNS: void
//
void Vector::VectorMagnitude(double xVector, double yVector)
{
	vectorMagnitude = sqrt(xVector*xVector + yVector*yVector);
}

//
// METHOD:ScaleMagnitude
// DESCRIPTION: scale the vectors magnitiude
// PARAMETERS:double scaleFactor
// RETURNS: void
//
void Vector::ScaleMagnitude(double scaleFactor)
{
	scaledMagnitude = vectorMagnitude * scaleFactor;
}

//
// METHOD:FrameRatio
// DESCRIPTION: calculate a ratio for an object to make translations in
//				its x and y coordinates smoothly
// PARAMETERS: (double xVector, double yVector
// RETURNS: void
//
void Vector::FrameRatio(double xVector, double yVector)
{
	VectorMagnitude(xVectorLength, yVectorLength);
	
	if (vectorMagnitude != 0)
	{
		xRatio = xVectorLength / vectorMagnitude;
		yRatio = yVectorLength / vectorMagnitude;
	}
}

//
// METHOD:GetYRatio
// DESCRIPTION: Accessor
// PARAMETERS: na
// RETURNS: double
//
double Vector::GetYRatio()
{
	return yRatio;
}

//
// METHOD:GetXRatio
// DESCRIPTION: Accessor
// PARAMETERS: na
// RETURNS: double
//
double Vector::GetXRatio()
{
	return xRatio;
}


//
// METHOD:GetYLength
// DESCRIPTION: Accessor
// PARAMETERS: na
// RETURNS: double
//
double Vector::GetYLength()
{
	return yVectorLength;
}

//
// METHOD:GetXLength
// DESCRIPTION: Accessor
// PARAMETERS: na
// RETURNS: double
//
double Vector::GetXLength()
{
	return xVectorLength;
}

//
// METHOD:GetMagnitude
// DESCRIPTION: Accessor
// PARAMETERS: na
// RETURNS: double
//
double Vector::GetMagnitude()
{
	return vectorMagnitude;
}

//
// METHOD:GetScaledMagnitude
// DESCRIPTION: Accessor
// PARAMETERS: na
// RETURNS: double
//
double Vector::GetScaledMagnitude()
{
	return scaledMagnitude;
}