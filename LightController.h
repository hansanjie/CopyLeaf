/*
 * LightController.h
 *
 *  Created on: 25.06.2018
 *      Author: Marco
 */

#ifndef LIGHTCONTROLLER_H_
#define LIGHTCONTROLLER_H_
#include "LEDPanel.h"
#include <iomanip>
#include <stdio.h>
#include <sstream>
#include <WS2812FX.h>

class LightController {
private:
	LEDPanel Panel[9];
	WS2812FX ws2812fx  = WS2812FX(27, 5, NEO_GRBW + NEO_KHZ800);
	int brightness = 0;

public:
	LightController();
	void fadeAllToColor (LEDColor c1, LEDColor c2, LEDColor c3, bool coldStart);
	void randomColor();
	void setBrightness(int b);
	int getBrightness();
	void setMode(int m);
	int getMode();
	void renderEffect();
	String getColor();

};

#endif /* LIGHTCONTROLLER_H_ */
