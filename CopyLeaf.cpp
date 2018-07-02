// Do not remove the include below
#include "CopyLeaf.h"

LightController lightCnt = LightController();
NetworkController netCnt = NetworkController(&lightCnt);


//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{
	netCnt.checkWebRequest();
	lightCnt.renderEffect();
}
