#include "LEDPanel.h"
 
LEDPanel::LEDPanel()
{
	index = -1;
}

LEDPanel::LEDPanel(int i)
{
    index = i;
}

//Fade LEDS of current panel to new color
void LEDPanel::fadeTo(WS2812FX* strip, int i, LEDColor c1, LEDColor c2, LEDColor c3, bool coldStart)
{
	if(coldStart && i==0)
	{
		LEDColor c = LEDColor(0,0,0,0);
		currCol1 = c;
		currCol2 = c;
		currCol3 = c;
	}
	currCol1.setR(currCol1.getR()   + (((c1.getR()   - currCol1.getR())   * i) / 255));
	currCol1.setG(currCol1.getG()   + (((c1.getG()   - currCol1.getG())   * i) / 255));
	currCol1.setB(currCol1.getB()   + (((c1.getB()   - currCol1.getB())   * i) / 255));
	currCol1.setW(currCol1.getW()   + (((c1.getW()   - currCol1.getW())   * i) / 255));

	currCol2.setR(currCol2.getR()   + (((c2.getR()   - currCol2.getR())   * i) / 255));
	currCol2.setG(currCol2.getG()   + (((c2.getG()   - currCol2.getG())   * i) / 255));
	currCol2.setB(currCol2.getB()   + (((c2.getB()   - currCol2.getB())   * i) / 255));
	currCol2.setW(currCol2.getW()   + (((c2.getW()   - currCol2.getW())   * i) / 255));

	currCol3.setR(currCol3.getR()   + (((c3.getR()   - currCol3.getR())   * i) / 255));
	currCol3.setG(currCol3.getG()   + (((c3.getG()   - currCol3.getG())   * i) / 255));
	currCol3.setB(currCol3.getB()   + (((c3.getB()   - currCol3.getB())   * i) / 255));
	currCol3.setW(currCol3.getW()   + (((c3.getW()   - currCol3.getW())   * i) / 255));

	strip->setPixelColor(3*index, currCol1.getR(), currCol1.getG(), currCol1.getB(), currCol1.getW());
	strip->setPixelColor(3*index + 1, currCol2.getR(), currCol2.getG(), currCol2.getB(), currCol2.getW());
	strip->setPixelColor(3*index + 2, currCol3.getR(), currCol3.getG(), currCol3.getB(), currCol3.getW());
}

LEDColor LEDPanel::getColor(int index){
	LEDColor retval = LEDColor(0,0,0,0);
	switch (index){
	case 0:
		retval = currCol1;
		break;
	case 1:
		retval = currCol2;
		break;
	case 2:
		retval = currCol3;
		break;
	}
	return retval;
}
