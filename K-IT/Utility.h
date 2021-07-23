#ifndef __UTILITY_H__
#define __UTILITY_H__

void delayAndPrint(int seconds) {
	for (auto i = 1; i <= seconds; ++i) {
		delay(1000);
		Serial.printf("%d ", i);
	}
	Serial.println();
}

void printStageChange(const char* label, byte previousState, byte currentState) {
	
	const char * previous = (previousState == HIGH ? "HIGH" : "LOW");
	const char* current = (currentState == HIGH ? "HIGH" : "LOW");
	
	Serial.printf("%s: %s -> %s\n", label, previous, current);
}

#endif