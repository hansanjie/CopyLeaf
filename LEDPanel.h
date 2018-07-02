#pragma once
#include "LEDColor.h"
#include <WS2812FX.h>


class LEDPanel
{
private:
    int index;
    LEDColor currCol1 = LEDColor(0,0,0,0);
    LEDColor currCol2 = LEDColor(0,0,0,0);
    LEDColor currCol3 = LEDColor(0,0,0,0);

public:
    LEDPanel();
    LEDPanel(int index);
    void fadeTo(WS2812FX* strip, int i, LEDColor c1, LEDColor c2, LEDColor c3, bool coldStart);
    LEDColor getColor(int index);

};
