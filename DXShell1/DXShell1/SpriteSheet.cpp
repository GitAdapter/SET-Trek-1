
/*
* FILENAME: SpriteSheet.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class SpriteSheet
*/

#include "SpriteSheet.h"

/****************************************************
The concept behind this class is that it will be passed
a filename and graphics object/rendertarget, then, will
proceed to create the needed WIC components to read, 
decode, and then encode the bitmap file from disk into
a compatible D2D bitmap. 

We need this approach to be able to address pretty much
any bitmap from disk/resources into the game and use it
within Directx (D2D specifically for now)

*******************************************************/

//
//	METHOD: SpriteSheet
//	DESCRIPTION: This method is a constructor for the SpriteSheet
//			     class, specifically it holds the WICFactories required
//				 for converting WIC style bitmaps to ID2D bitmaps
//	PARAMETERS:  wchar_t* filename
//			     Graphics* gfx
//	RETURNS: N/A
//
SpriteSheet::SpriteSheet(wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx; //save the gfx parameter for later
	bmp = NULL; //This needs to be NULL to start off
	HRESULT hr;

	//Step 1: Create a WIC Factory
	IWICImagingFactory2 *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory, //CLS ID of the object about to be made
		NULL, //not needed here, but just denotes this isn't part of an aggregate
		CLSCTX_INPROC_SERVER, //Indicates this DLL runs in the same process
		IID_IWICImagingFactory, //Reference to an Interface that talks to the object
		(LPVOID*)&wicFactory); //This is our pointer to the WICFactory, once set up.

//Step 2: Create a Decoder to read file into a WIC Bitmap
	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename, //The filename we passed in already
		NULL, //This can be used to indicate other/preferred decoders. Not something we need.
		GENERIC_READ, //indicates we're reading from the file, vs writing, etc.
		WICDecodeMetadataCacheOnLoad, //Needed, but would only help if we were keeping this in WIC
		&wicDecoder); //Our pointer to the Decoder we've setup

//Step 3: Read a 'frame'. We're really just moving the whole image into a frame here
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame); //0 here means the first frame... or only one in our case
	//Now, we've got a WICBitmap... we want it to be a D2D bitmap

//Step 4: Create a WIC Converter
	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

//Step 5: Configure the Converter
	hr = wicConverter->Initialize(
		wicFrame, //Our frame from above
		GUID_WICPixelFormat32bppPBGRA, //Pixelformat
		WICBitmapDitherTypeNone, //not important for us here
		NULL, //indicates no palette is needed, not important here
		0.0, //Alpha Transparency, can look at this later
		WICBitmapPaletteTypeCustom //Not important for us here
		);

//Step 6: Create the D2D Bitmap! Finally!
	gfx->GetDeviceContext()->CreateBitmapFromWicBitmap(
		wicConverter, //Our friend the converter
		NULL, //Can specify D2D1_Bitmap_Properties here, not needed now
		&bmp //Our destination bmp we specified earlier in the header
	);
	
	//Let us do some private object cleanup!
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();
}


//ID2D1Bitmap* SpriteSheet::GetCurrentBitmap()
//{
//	return bmp;
//}

void SpriteSheet::CompositeEffect(ID2D1Image* base, ID2D1Image* detail)
{
	gfx->GetDeviceContext()->CreateEffect(CLSID_D2D1Composite, &compositeEffect);

	compositeEffect->SetInput(0, base);
	compositeEffect->SetInput(1, detail);
}

void SpriteSheet::SetImage()
{
	scale->GetOutput(&EffectImage);
}

ID2D1Image* SpriteSheet::GetImage()
{
	return EffectImage;
}




//
//	METHOD: ChromaKeyEffect()
//	DESCRIPTION: This method chains the effects ChromaKey and Scaling to a specified bitmap
//				 once all effects have been chained, use the final ID2D1Effect* to draw a Image
//				 to the client window.
//	PARAMETERS: float firstX,
//			    float firstY,
//			    float secondX,
//				float secondY
//	RETURNS: void
//
void SpriteSheet::ChromaKeyEffect(float firstX, float firstY, float secondX, float secondY, int colorFlag)
{
	//get sector height and width
	float screenHeight = gfx->GetDeviceContext()->GetSize().height/10;
	float screenWidth = gfx->GetDeviceContext()->GetSize().width/10 ;

	//create chroma key and scale effects
	gfx->GetDeviceContext()->CreateEffect(CLSID_D2D1ChromaKey, &chromaKey);
	gfx->GetDeviceContext()->CreateEffect(CLSID_D2D1Scale, &scale);
	// set chroma key effect to current bitmap
	chromaKey->SetInput(0, bmp);
	//set hex value to chromakey (lime green in this case)
	if (colorFlag == 1)
	{
		chromaKey->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.0f, 1.0f, 0.0f));
	}
	else
	{
		chromaKey->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.0f, 0.0f, 1.0f));
	}
	chromaKey->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.75f); //set the tolerance
	chromaKey->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, 0); //set Invert Alpha to false
	chromaKey->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, 0); //set prop feather to false

	 //use coordinates to scale bitmap to a sector
	scale->SetValue(D2D1_SCALE_PROP_SCALE, D2D1::Vector2F(screenWidth /
		bmp->GetSize().width, screenHeight / bmp->GetSize().height));
	scale->SetInputEffect(0, chromaKey); // chain effects
	scale->SetInput(1, bmp); // set chain to bitmap
}

//void SpriteSheet::ChromaKeyEffect(SpriteSheet* classDetails, int firstX, int firstY, int secondX, int secondY)
//{
//	int screenHeight = gfx->GetDeviceContext()->GetSize().height;
//	int screenWidth = gfx->GetDeviceContext()->GetSize().width;
//
//	gfx->GetDeviceContext()->CreateEffect(CLSID_D2D1ChromaKey, &chromaKey);
//	gfx->GetDeviceContext()->CreateEffect(CLSID_D2D1Scale, &scale);
//
//	chromaKey->SetInput(0, bmp);
//	chromaKey->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.0f, 1.0f, 0.0f));
//	chromaKey->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.75f);
//	chromaKey->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, 0);
//	chromaKey->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, 0);
//
//	// (x2-x1)/bmp->GetSize().width, (y2-y1)/bmp->GetSize().height
//	scale->SetValue(D2D1_SCALE_PROP_SCALE, D2D1::Vector2F(0.75f, 0.75f));
//	scale->SetInputEffect(0, chromaKey);
//	scale->SetInput(1, bmp);
//
//	D2D_POINT_2F point;
//	//bmp-> chromaKey;
//}







ID2D1Bitmap1* SpriteSheet::GetCurrentBitmap() {
	return bmp;
}

//void SpriteSheet::SetCurrentBitmap(ID2D1Bitmap1* newBitmap) {
//	bmp = newBitmap;
//}


ID2D1Effect* SpriteSheet::GetChromaEffect() {
	return scale;
}


//
//	METHOD: Draw()
//	DESCRIPTION: This method draws a bitmap to a destination triangle
//				 onto a source triangle. Destination being a sector on
//			     the Client window and the Client window being the Source.
//	PARAMETERS: N/A
//	RETURN: N/A
//
void SpriteSheet::Draw()
{
	gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F(0,0)));
	gfx->GetDeviceContext()->DrawBitmap(
		bmp, //Bitmap we built from WIC
		D2D1::RectF(0, 0,
			gfx->GetDeviceContext()->GetSize().width, gfx->GetDeviceContext()->GetSize().height), //Destination rectangle
		0.8f, //Opacity or Alpha
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		//Above - the interpolation mode to use if this object is 'stretched' or 'shrunk'. 
		//Refer back to lecture notes on image/bitmap files
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height) //Source Rect
		);
}

SpriteSheet::~SpriteSheet()
{
	if (bmp) bmp->Release();
}

void SpriteSheet::Draw(float firstX, float firstY, float secondX, float secondY)
{
	D2D_POINT_2F point;
	gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F(0, 0)));
	point = { (float)firstX, (float)firstY };
	gfx->GetDeviceContext()->DrawImage(scale, point);
}


//
//	METHOD: Draw
//	DESCRIPTION: This method writes Gameobjects to the client window,
//				 it takes a Image with effected chained to tit along with,
//				 a starting coordinate to draw from.
//	PARAMETERS: float firstX,
//				float firstY,
//				float secondX,
//				float secondY
//
//
//
//	RETURNS: void
//
void SpriteSheet::Draw(float firstX, float firstY, float orientation)
{
	float sectorWidth = gfx->GetDeviceContext()->GetSize().width / 10;
	float sectorHeight = gfx->GetDeviceContext()->GetSize().height / 10;
	D2D_POINT_2F point = { firstX, firstY };
	gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Rotation(orientation, D2D1::Point2F(firstX+(sectorWidth/2), firstY+(sectorHeight/2))));
	gfx->GetDeviceContext()->DrawImage(scale, point);
}
