#ifndef __UTILITY_H__
#define __UTILITY_H__

void delayAndPrint(int seconds) {
	for (auto i = 1; i <= seconds; ++i) {
		delay(1000);
		Serial.printf("%d ", i);
	}
	Serial.println();
}

void printStageChange(const String& label, byte previousState, byte currentState) {
	Serial.print(label);
	Serial.print(previousState == HIGH ? "HIGH" : "LOW");
	Serial.print(" -> ");
	Serial.print(currentState == HIGH ? "HIGH" : "LOW");
	Serial.print("\n");
}

#endif