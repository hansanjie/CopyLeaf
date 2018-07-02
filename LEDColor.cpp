#include "LEDColor.h"
LEDColor::LEDColor(int r, int g, int b, int w)
 {
     rVal = r;
     gVal = g;
     bVal = b;
     wVal = w;
 }

void LEDColor::setR(int val)
{
	rVal = val;
}

void LEDColor::setG(int val)
{
	gVal = val;
}

void LEDColor::setB(int val)
{
	bVal = val;
}

void LEDColor::setW(int val)
{
	wVal = val;
}

int LEDColor::getR()
{
    return rVal;
}

int LEDColor::getG()
{
    return gVal;
}

int LEDColor::getB()
{
    return bVal;
}

int LEDColor::getW()
{
    return wVal;
}
