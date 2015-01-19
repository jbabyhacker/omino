#include <Arduino.h>

#ifdef TIME_DEBUG
	long startTime = 0;
#endif

byte melody, rhythm;

boolean checkForMessage(){
	if(Serial.available() > 2){
		byte in = Serial.read();
		if(in == 0xAA){
			melody = Serial.read();
			rhythm = Serial.read();
			return true;
		}
	}
	return false;
}

void waitForBeat(){
#ifdef TIME_DEBUG
	if(startTime) Serial.println(millis() - startTime);
	startTime = millis();
#else
	while(!checkForMessage());
#endif
}

void connectInstrument(){
	Serial.begin(9600);
#ifdef TIME_DEBUG
	Serial.println("start");
#endif
}
