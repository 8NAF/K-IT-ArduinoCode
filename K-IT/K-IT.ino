#include "Utility.h"
#include "Notification.h"
#include "setup_Arduino.h"
#include "setup_Firebase.h"

void setup() {

	Serial.begin(115200);

	setup_WiFi();
	setup_FirebaseRealtimeDatabase();
	setup_FirebaseCloudMessaging();
	setup_callback();
	setup_pin();
}


auto notification = Notification();
byte previousState = LOW;
byte currentState = LOW;

void notifyClient() {

	//Title, body, [icon, [action]]
	fcm.fcm.setNotifyMessage("Chú ý", "Cảnh báo có trộm");

	// Data: dạng key - value
	String data = R"({"notificationId":")" + notification.currentId + R"("})";
	Serial.println("data: " + data);
	//fcm.fcm.addCustomNotifyMessage("notificationId", notification.currentId);
	fcm.fcm.setDataMessage(data);
	
	// Gửi đến thiết bị đầu tiên đăng ký
	bool success = Firebase.sendMessage(fcm, 0);
	if (success) {
		Serial.println("Send notification to client success");
	}
	else {
		Serial.println("Error Sending notification to client: " + fcm.errorReason());
	}


}

bool isReady() {
	if (!Firebase.ready()) {
		Serial.println("Firebase not ready");
		return false;
	}
	
	if (!hasToken) {
		Serial.println("Not has token");
		return false;
	}
	
	if (delayNotificationSeconds < 0) {
		Serial.println("Not has delay notification seconds");
		return false;
	}
	
	return true;
}

void loop() {

	// Chờ cho đến khi mọi thứ sẵn sàng
	if (!isReady()) {
		return;
	}

	// Nếu người dùng tắt nhận thông báo thì dừng đọc cảm biến
	// Sau đó xử lý nếu thông báo vẫn đang high
	if (turnOffNotification) {

		Serial.println("Set end because user turn off");

		// Nếu như tắt thông báo khi báo động chưa kết thúc, đặt end bằng thời gian hiện tại
		// sau đó delay thời gian giữa những lần thông báo
		digitalWrite(LED, LOW);
		previousState = LOW;
		
		if (notification.setEnd()) {
			Serial.printf("Delay after set end: %d\n", delayNotificationSeconds);
			delayAndPrint(delayNotificationSeconds);
		}
		return;
	}

	// Nếu cảm biến chuyển từ trạng thái LOW sang HIGH
	currentState = digitalRead(PIR);

	if (previousState == LOW and currentState == HIGH) {

		printStageChange("Stage change (L->H): ", previousState, currentState);

		// Khởi tạo một notification mới trên firebase
		// Gán start bằng thời gia hiện tại
		// Gán isReceived bằng false
		notification.init();
		delayAndPrint(15);


		currentState = digitalRead(PIR);
		printStageChange("Stage change (H->15): ", previousState, currentState);

		// Nếu sau 15s mà cảm biến vẫn HIGH thì
		// - gán end bằng thời gian hiên tại (nhưng không reset lại currentId)
		// - thông báo cho app Android
		// - bật led
		if (currentState == HIGH) {
			Serial.println("Set end because data need be formatted");
			notification.setEnd(false);
			notifyClient();

			digitalWrite(LED, HIGH);
			previousState = HIGH;
		}
		// Ngược lại (cảm biến LOW) thì rollback notification đã push lên firebase
		else {
			notification.rollback();
		}
	}

	// Nếu cảm biến chuyển từ trạng thái HIGH sang LOW
	currentState = digitalRead(PIR);

	if (previousState == HIGH and currentState == LOW) {

		printStageChange("Stage change (H->L): ", previousState, currentState);

		Serial.println("Set end because sensor is low");
		
		digitalWrite(LED, LOW);
		previousState = LOW;
		
		if (notification.setEnd()) {
			Serial.printf("Delay after set end: %d\n", delayNotificationSeconds);
			delayAndPrint(delayNotificationSeconds);
		}
	}
}