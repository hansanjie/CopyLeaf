/*
 * NetworkController.h
 *
 *  Created on: 13.06.2018
 *      Author: Marco
 */

#ifndef NETWORKCONTROLLER_H_
#define NETWORKCONTROLLER_H_

#include <ESP8266WiFi.h>
#include <stdlib.h>     /* strtol */
#include <string>
#include <ESP8266WebServer.h>
#include "LightController.h"

class NetworkController {

private:
	const char* ssid_c = "xxx";
	const char* password_c = "xxx";
	IPAddress ip_c = IPAddress(192, 168, 178, 15);   // set a fixed IP for the NodeMCU
	IPAddress gateway_c = IPAddress(192, 168, 178, 1); // Your router IP
	IPAddress subnet_c = IPAddress(255, 255, 255, 0); // Subnet mask

	ESP8266WebServer* server = new ESP8266WebServer(80);
	LightController* lightCnt;

	void WiFiStart();
	void handleColor();
	void handleBrightness();
	void handleState();
	void handleEffect1();

public:
	NetworkController(LightController* controller);
	void checkWebRequest();
};

#endif /* NETWORKCONTROLLER_H_ */
