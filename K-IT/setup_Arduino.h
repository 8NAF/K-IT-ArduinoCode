#ifndef __SETUP_ARDUINO_H__
#define __SETUP_ARDUINO_H__


#if defined(ESP32)
	#include <WiFi.h>
#elif defined(ESP8266)
	#include <ESP8266WiFi.h>
#endif


#define WIFI_SSID "Nhat Le"
#define WIFI_PASSWORD "dua50000"

void setup_WiFi() {


	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	Serial.print("Connecting to Wi-Fi");

	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(300);
	}

	Serial.print("\nConnected with IP: ");
	Serial.println(WiFi.localIP());
}


constexpr byte PIR = D6;
constexpr byte LED = D1;

void setup_pin() {
	pinMode(LED, OUTPUT);
	pinMode(PIR, INPUT);
}

#endif