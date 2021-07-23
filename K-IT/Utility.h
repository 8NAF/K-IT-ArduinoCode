#ifndef __UTILITY_H__
#define __UTILITY_H__

void delayAndPrint(int seconds) {
	for (auto i = 1UL; i <= seconds; ++i) {
		Serial.printf("%d ", i);
		delay(1000);
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