#ifndef __SETUP_FIREBASE_H__
#define __SETUP_FIREBASE_H__


#if defined(ESP32)
	#include <FirebaseESP32.h>
#elif defined(ESP8266)
	#include <FirebaseESP8266.h>
#endif

#include "Utility.h"

#define DATABASE_URL "k-it-283d4-default-rtdb.asia-southeast1.firebasedatabase.app"
#define DATABASE_SECRET "H9HszprK8pUExtW2pp8pbrIdw1gfHy6Y3mUboMg9"

void setup_FirebaseRealtimeDatabase() {
	Serial.printf("\nFirebase Client v%s\n", FIREBASE_CLIENT_VERSION);
	Firebase.begin(DATABASE_URL, DATABASE_SECRET);
	Firebase.reconnectWiFi(true);
}


#define FIREBASE_FCM_SERVER_KEY "AAAAjG_4oNo:APA91bGSDr0kIFn6g11TLXIEZeLd5_7yKxh_TTUO-Cj5ZADfU-VmHYHxuEqCvdPKtyo21UY0fRvlDwru1qMKFS-iNMlZ1GXhf8iMBadvAsmnH5XIYWtVIxEWFLwvUR0H4SkpknIKJwzj"
FirebaseData fcm = FirebaseData();

void setup_FirebaseCloudMessaging() {
	Serial.println("FCM Server started");
	
	fcm.fcm.begin(FIREBASE_FCM_SERVER_KEY);
	fcm.fcm.setPriority("high");
	fcm.fcm.setCollapseKey("K-IT");
	fcm.fcm.setTimeToLive(900); // 15 phút
}



const String parentPath = "/applicationConfiguration";
String childPath[3] = {
	"/FCMRegistrationToken",
	"/turnOnNotification",
	"/delayNotificationSeconds",
};

int delayNotificationSeconds = -1;
bool turnOffNotification;
bool hasToken = false;

void multiPathDataCallback(MultiPathStreamData stream) {

	// Nếu FCMRegistrationToken có thay dổi
	if (stream.get(childPath[0])) {
		Serial.println("FCMRegistrationToken change");
		Serial.printf("Original value: %s\n", stream.value.c_str());

		hasToken = true;
		String newToken = stream.value;

		// Xóa token cũ đi
		fcm.fcm.removeDeviceToken(0);
		// Thêm token mới vào
		fcm.fcm.addDeviceToken(newToken);

		Serial.print("Converted value: ");
		Serial.println(newToken);
		delayAndPrint(5);
	}

	//Nếu turnOffNotification có thay đổi
	if (stream.get(childPath[1])) {
		Serial.println("turnOffNotification change");
		Serial.printf("Original value: %s\n", stream.value.c_str());

		turnOffNotification = (stream.value == "false");
		Serial.print("Converted value: ");
		Serial.println(turnOffNotification ? "true" : "false");
		delayAndPrint(5);
	}

	// Nếu delayNotificationSeconds có thay đổi
	if (stream.get(childPath[2])) {

		Serial.println("delayNotificationSeconds change");
		Serial.printf("Original value: %s\n", stream.value.c_str());

		delayNotificationSeconds = stream.value.toInt();
		Serial.printf("Converted value: %d\n", delayNotificationSeconds);
		delayAndPrint(5);
	}
}

void timeoutCallback(bool timeout) {
	if (timeout) {
		Serial.println("Stream timeout, resuming...");
	}
}

FirebaseData multiStream;

void setup_callback() {

	// Thử lại liên tục cho đến khi đăng ký lắng nghe sự kiện thành công
	while (!Firebase.beginMultiPathStream(multiStream, parentPath, childPath, 3)) {
		Serial.printf("\nMulti path stream begin error, %s\n", multiStream.errorReason().c_str());
	}

	Firebase.setMultiPathStreamCallback(multiStream, multiPathDataCallback, timeoutCallback);
}


#endif