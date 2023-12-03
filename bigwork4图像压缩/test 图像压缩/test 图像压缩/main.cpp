#include <stdio.h>
#include "jpeg_encoder.h"

//-------------------------------------------------------------------------------
int main()
{
	const char* inputFileName = "lena.bmp";

	JpegEncoder encoder;
	if (!encoder.readFromBMP(inputFileName))
	{
		return 1;
	}

	if (!encoder.encodeToJPG("out.jpg", 199))
	{
		return 1;
	}
	return 0;
}