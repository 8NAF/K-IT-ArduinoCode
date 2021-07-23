#ifndef __NOTIFICATION_H__
#define __NOTIFICATION_H__

#if defined(ESP32)
	#include <FirebaseESP32.h>
#elif defined(ESP8266)
	#include <FirebaseESP8266.h>
#endif

class Notification {

private:
	inline static FirebaseData data = FirebaseData();
	inline static const String rootPath = "/logs";

public:

	String currentId = "";

	void init() {

		FirebaseJson notification;

		notification.add("start", 0);
		notification.add("end", 0);
		notification.add("isReceived", false);

		bool success = Firebase.pushJSON(data, rootPath, notification);

		if (success) {
			currentId = data.pushName();
			Serial.println("Push success: " + rootPath);
			Serial.println("New key: " + currentId);

			String path = rootPath + "/" + currentId + "/" + "start";
			success = Firebase.setTimestamp(data, path);
			if (success) {
				Serial.println("Set start timestamp success: " + path);
				Serial.println("Timestamp: " + String(data.floatData()));
			}
			else {
				Serial.println("Error set start timestamp: " + path);
				Serial.println("Message: " + data.errorReason());
			}
		}
		else {
			currentId = "";
			Serial.println("Error pushing: " + rootPath);
			Serial.println("Message: " + data.errorReason());
		}
	}

	bool setEnd(bool isResetCurrentId = true) {

		if (currentId == "") {
			return false;
		}

		String path = rootPath + "/" + currentId + "/" + "end";
		bool success = Firebase.setTimestamp(data, path);

		if (success) {
			Serial.println("Set end timestamp success: " + path);
			Serial.println("Timestamp: " + String(data.floatData()));
			if (isResetCurrentId) {
				currentId = "";
			}
		}
		else {
			Serial.println("Error set end timestamp: " + path);
			Serial.println("Message: " + data.errorReason());
		}

		return success;
	}

	void rollback() {

		if (currentId == "") {
			return;
		}

		String path = rootPath + "/" + currentId;
		bool success = Firebase.deleteNode(data, path);

		if (success) {
			Serial.println("Delete node success: " + path);
			currentId = "";
		}
		else {
			Serial.println("Delete node error: " + path);
			Serial.println("Message: " + data.errorReason());
		}
	}
};

#endif