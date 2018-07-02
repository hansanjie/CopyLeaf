/*
 * LightController.cpp
 *
 *  Created on: 25.06.2018
 *      Author: Marco
 */

#include "LightController.h"

LightController::LightController() {
	randomSeed(analogRead(16));

	ws2812fx.init();
	ws2812fx.setBrightness(255);
	brightness = 255;
	ws2812fx.setSpeed(200);
	ws2812fx.setMode(FX_MODE_STATIC);
	ws2812fx.start();

	for (int i=0; i<9; i++)
	{
		Panel[i] = LEDPanel(i);
	}
}

//Fade all Panels to same color
void LightController::fadeAllToColor (LEDColor c1, LEDColor c2, LEDColor c3, bool coldStart)
{
	for (int j = 0; j <= 255; j++)
	{
		for(int i=0; i<9; i++)
		{
			Panel[i].fadeTo(&ws2812fx, j, c1, c2, c3, coldStart);
		}
		ws2812fx.show();
		delay(5);
	}
}

void LightController::randomColor()
{
	int RandNr = random(1, 100001);
	if (RandNr % 20000 == 0)
	{
		int PanelNr = random(0, 9);
		int g = random(0, 256);
		LEDColor c = LEDColor(255, g, 0, 0);
		for (int i = 0; i <= 255; i++)
		{
			Panel[PanelNr].fadeTo(&ws2812fx, i, c, c, c, false);
			ws2812fx.show();
		}
	}
}

//if non static color set (i.e. effect) render effect
void LightController::renderEffect()
{
	if(ws2812fx.getMode()!=0)
	{
		ws2812fx.service();
	}
}

void LightController::setBrightness(int b)
{
	//check if strip starts from 0 brightness
	bool coldStart = (brightness==0);

	//if strip already on
	if(!coldStart)
	{
		//smooth fade to desired brightness
		for (int i=0; i<=255; i++)
		{
			brightness = (brightness   + (((b   - brightness)   * i) / 255));
			ws2812fx.setBrightness(brightness);
			ws2812fx.show();
			delay(5);
		}
	}
	//if starting from 0 brightness
	else
	{
		ws2812fx.start();

		//set brightness
		ws2812fx.setBrightness(b);
		brightness = b;

		//fade strip to last color
		LEDColor c = Panel[0].getColor(0);
		fadeAllToColor(c, c, c, true);
	}
}

int LightController::getBrightness()
{
	return (int)brightness/2.55;
}

String LightController::getColor()
{
	//get current color frpm Panel
	LEDColor currCol = Panel[0].getColor(0);

	//Transgorm rgb to 6 digit HEX string
	int i = currCol.getR() * 16 * 16 * 16 *16;
	i += currCol.getG() * 16 * 16;
	i += currCol.getB();
	String s(i, HEX);

	//if rgb are all 0
	if(i == 0)
	{
		//transform white value to rgb for HEX convert
		int j = currCol.getW() * 16 * 16 * 16 *16;
		j += currCol.getW() * 16 * 16;
		j += currCol.getW();

		//if white is 0, strip is set to black
		if(j==0)
		{
			s="000000";
		}
		//if strip is set to white
		else
		{
			s=String(j, HEX);
		}
	}

	//if red is 0 and everything else is non 0, force write 00 to hex string
	else if(currCol.getR()==0 && i != 0)
	{
		s = "00" + s;
	}

	//if red value  smaller 16 write 0 in front
	else if (currCol.getR()<16 && currCol.getR() != 0 && i != 0)
	{
		s = "0" + s;
	}
	return s;
}

void LightController::setMode(int m)
{
	ws2812fx.setMode(m);
}

int LightController::getMode()
{
	return ws2812fx.getMode();
}
