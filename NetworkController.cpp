/*
 * NetworkController.cpp
 *
 *  Created on: 13.06.2018
 *      Author: Marco
 */

#include "NetworkController.h"

NetworkController::NetworkController(LightController* controller) {
	lightCnt = controller;
	WiFiStart();
}

void NetworkController::WiFiStart() {
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid_c, password_c);
	WiFi.config(ip_c, gateway_c, subnet_c);
	server->begin();
	server->on("/color", std::bind(&NetworkController::handleColor, this));
	server->on("/brightness", std::bind(&NetworkController::handleBrightness, this));
	server->on("/state", std::bind(&NetworkController::handleState, this));
	server->on("/effect1", std::bind(&NetworkController::handleEffect1, this));
}

void NetworkController::checkWebRequest(){
	server->handleClient();
}

//Handler for different urls
void NetworkController::handleColor() {
	String hexstring = server->arg("color");
	if(hexstring == ""){
		server->send(200, "text/plain", lightCnt->getColor());   // Send HTTP status 200 (Ok) and send some text to the browser/client
	}
	else{
		hexstring = "#" + hexstring;
		server->send(200, "text/plain", "success");
		// Get rid of '#' and convert it to integer
		int number = (int) strtol( &hexstring[1], NULL, 16);

		// Split them up into r, g, b values
		int r = number >> 16;
		int g = number >> 8 & 0xFF;
		int b = number & 0xFF;
		LEDColor c = LEDColor(r, g, b, 0);
		if ((r == g) && (r == b))
		{
			c = LEDColor(0, 0, 0, r);
		}
		lightCnt->setMode(0);
		lightCnt->fadeAllToColor(c, c, c, false);
	}

}

void NetworkController::handleBrightness() {
	String brightness = server->arg("brightness");
	if(brightness == ""){
		String s = String(lightCnt->getBrightness());
		server->send(200, "text/plain", s);   // Send HTTP status 200 (Ok) and send some text to the browser/client
	}
	else{
		server->send(200, "text/plain", "success");
		// Get rid of '#' and convert it to integer
		int number = (int) strtol( &brightness[0], NULL, 10);
		lightCnt->setBrightness(number*2.55);
	}

}

void NetworkController::handleState() {
	String state = server->arg("state");
	if(state == ""){
		String s = (lightCnt->getBrightness() == 0) ? "0" : "1";
		server->send(200, "text/plain", s);   // Send HTTP status 200 (Ok) and send some text to the browser/client
	}
	else{
		server->send(200, "text/plain", "success");
		if(state=="1")
		{
			lightCnt->setBrightness(255);
		}
		else
		{
			lightCnt->setBrightness(0);
		}
	}

}

void NetworkController::handleEffect1() {
	String enabled = server->arg("enabled");
	if(enabled == ""){
		String s = (lightCnt->getMode() == 11) ? "1" : "0";
		server->send(200, "text/plain", s);   // Send HTTP status 200 (Ok) and send some text to the browser/client
	}
	else{
		server->send(200, "text/plain", "success");

		lightCnt->setMode(11);
	}

}
