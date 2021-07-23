//#if defined(ESP32)

//#include <WiFi.h>
//#include <FirebaseESP32.h>

//#elif defined(ESP8266)

//#include <ESP8266WiFi.h>
//#include <FirebaseESP8266.h>

//#endif

#pragma region Utility
//void delayAndPrint(int seconds) {
//	for (auto i = 1UL; i <= seconds; ++i) {
//		Serial.printf("%d ", i);
//		delay(1000);
//	}
//	Serial.println();
//}

//void printStageChange(const String& label, byte previousState, byte currentState) {
//	Serial.print(label);
//	Serial.print(previousState == HIGH ? "HIGH" : "LOW");
//	Serial.print(" -> ");
//	Serial.print(currentState == HIGH ? "HIGH" : "LOW");
//	Serial.print("\n");
//}
#pragma endregion
#pragma region Notification

//class Notification {

//private:
//	inline static FirebaseData data = FirebaseData();

//public:

//	inline static const String rootPath = "/logs";

//	String currentId = "";

//	void init() {

//		FirebaseJson notification;

//		notification.add("start", 0);
//		notification.add("end", 0);
//		notification.add("isReceived", false);

//		bool success = Firebase.pushJSON(data, rootPath, notification);

//		if (success) {
//			currentId = data.pushName();
//			Serial.println("Push success: " + rootPath);
//			Serial.println("New key: " + currentId);

//			String path = rootPath + "/" + currentId + "/" + "start";
//			success = Firebase.setTimestamp(data, path);
//			if (success) {
//				Serial.println("Set start timestamp success: " + path);
//				Serial.println("Timestamp: " + String(data.floatData()));
//			}
//			else {
//				Serial.println("Error set start timestamp: " + path);
//				Serial.println("Message: " + data.errorReason());
//			}
//		}
//		else {
//			currentId = "";
//			Serial.println("Error pushing: " + rootPath);
//			Serial.println("Message: " + data.errorReason());
//		}
//	}

//	bool setEnd(bool isResetCurrentId = true) {

//		if (currentId == "") {
//			return false;
//		}

//		String path = rootPath + "/" + currentId + "/" + "end";
//		bool success = Firebase.setTimestamp(data, path);

//		if (success) {
//			Serial.println("Set end timestamp success: " + path);
//			Serial.println("Timestamp: " + String(data.floatData()));
//			if (isResetCurrentId) {
//				currentId = "";
//			}
//		}
//		else {
//			Serial.println("Error set end timestamp: " + path);
//			Serial.println("Message: " + data.errorReason());
//		}

//		return success;
//	}

//	void rollback() {

//		if (currentId == "") {
//			return;
//		}

//		String path = rootPath + "/" + currentId;
//		bool success = Firebase.deleteNode(data, path);

//		if (success) {
//			Serial.println("Delete node success: " + path);
//			currentId = "";
//		}
//		else {
//			Serial.println("Delete node error: " + path);
//			Serial.println("Message: " + data.errorReason());
//		}
//	}
//};

#pragma endregion
#pragma region setup Firebase

//#define DATABASE_URL "k-it-283d4-default-rtdb.asia-southeast1.firebasedatabase.app"
//#define DATABASE_SECRET "H9HszprK8pUExtW2pp8pbrIdw1gfHy6Y3mUboMg9"

//void setup_FirebaseDatabase() {
//	Serial.printf("\nFirebase Client v%s\n", FIREBASE_CLIENT_VERSION);
//	Firebase.begin(DATABASE_URL, DATABASE_SECRET);
//	Firebase.reconnectWiFi(true);
//}

//#define FIREBASE_FCM_SERVER_KEY "AAAAjG_4oNo:APA91bGSDr0kIFn6g11TLXIEZeLd5_7yKxh_TTUO-Cj5ZADfU-VmHYHxuEqCvdPKtyo21UY0fRvlDwru1qMKFS-iNMlZ1GXhf8iMBadvAsmnH5XIYWtVIxEWFLwvUR0H4SkpknIKJwzj"
//FirebaseData fcm = FirebaseData();

//void setup_FirebaseCloudMessage() {
//	Serial.println("FCM Server started");
//	fcm.fcm.begin(FIREBASE_FCM_SERVER_KEY);
//	fcm.fcm.setPriority("high");
//	fcm.fcm.setCollapseKey("K-IT");
//	fcm.fcm.setTimeToLive(900); // 15 phút
//}

//String childPath[3] = {
//	"/FCMRegistrationToken",
//	"/turnOnNotification",
//	"/delayNotificationSeconds",
//};

//int delayNotificationSeconds = -1;
//bool turnOffNotification;
//bool hasToken = false;

//void multiPathDataCallback(MultiPathStreamData stream) {

//	// Nếu FCMRegistrationToken có thay dổi
//	if (stream.get(childPath[0])) {
//		Serial.println("FCMRegistrationToken change");
//		Serial.printf("Original value: %s\n", stream.value.c_str());

//		hasToken = true;
//		String newToken = stream.value;

//		// Xóa token cũ đi
//		fcm.fcm.removeDeviceToken(0);
//		// Thêm token mới vào
//		fcm.fcm.addDeviceToken(newToken);

//		Serial.print("Converted value: ");
//		Serial.println(newToken);
//		delayAndPrint(5);
//	}

//	//Nếu turnOffNotification có thay đổi
//	if (stream.get(childPath[1])) {
//		Serial.println("turnOffNotification change");
//		Serial.printf("Original value: %s\n", stream.value.c_str());

//		turnOffNotification = (stream.value == "false");
//		Serial.print("Converted value: ");
//		Serial.println(turnOffNotification ? "true" : "false");
//		delayAndPrint(5);
//	}

//	// Nếu delayNotificationSeconds có thay đổi
//	if (stream.get(childPath[2])) {

//		Serial.println("delayNotificationSeconds change");
//		Serial.printf("Original value: %s\n", stream.value.c_str());

//		delayNotificationSeconds = stream.value.toInt();
//		Serial.printf("Converted value: %d\n", delayNotificationSeconds);
//		delayAndPrint(5);
//	}
//}

//void timeoutCallback(bool timeout) {
//	if (timeout) {
//		Serial.println("Stream timeout, resuming...");
//	}
//}

////FirebaseData stream;
//FirebaseData multiStream;

//void setup_callback() {


//	// Thử lại liên tục cho đến khi đăng ký lắng nghe sự kiện thành công
//	while (!Firebase.beginMultiPathStream(multiStream, "/applicationConfiguration", childPath, 3)) {
//		Serial.printf("\nMulti path stream begin error, %s\n", multiStream.errorReason().c_str());
//	}

//	//while (!Firebase.beginStream(stream, "/applicationConfiguration")) {
//	//	Serial.printf("\nStream begin error, %s\n", stream.errorReason().c_str());
//	//}

//	Firebase.setMultiPathStreamCallback(multiStream, multiPathDataCallback, timeoutCallback);
//}

#pragma endregion
#pragma region setup Arduino

//#define WIFI_SSID "Nhat Le"
//#define WIFI_PASSWORD "dua50000"

//void setup_WiFi() {

//	Serial.begin(115200);

//	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//	Serial.print("Connecting to Wi-Fi");

//	while (WiFi.status() != WL_CONNECTED) {
//		Serial.print(".");
//		delay(300);
//	}

//	Serial.print("\nConnected with IP: ");
//	Serial.println(WiFi.localIP());
//}


//constexpr byte PIR = D6;
//constexpr byte LED = D1;

//void setup_pin() {
//	pinMode(LED, OUTPUT);
//	pinMode(PIR, INPUT);
//}

#pragma endregion