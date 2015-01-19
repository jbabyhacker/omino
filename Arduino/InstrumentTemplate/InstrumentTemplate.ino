/* Template for Class-wide Instrument Integration

Written by Alexander O'Brien, 10/13/2014

This template and included header file are meant to make it easy to create a network of automated instruments.
The Arduino controlling each instrument shall be connected to the main control computer via USB.
The Controller will be sending one serial packet per measure, which at 160BPM is approx. every 1.5 seconds.

To write custom Phrases and Rhythms, the user of the template simply has to modify the numbers in the arrays below,
and add code that will play pitches on their respective instrument in the playPitch function.
There should be 10 phrases and 10 rhythms with 4 beats each. This ensures that the group can play music together.

IMPORTANT:
It has been suggested that we play music at 160BPM. For the sake of synchronization,
the execution of the playMeasure function cannot exceed 1500 ms. Notice that in the template provided,
the numbers in the rhythmData array add to 1500. In reality, writing to servos and toggling pins takes some time.
The user will need to do some debugging to find what times are appropriate. The goal should be to have playMeasure execute in ~1480-1490ms.

A benchmark function has been included to assist in meeting this goal, simply leave TIME_DEBUG uncommented below and execution time
will be printed to the serial monitor. When connecting to the instrument network, this line MUST be commented out.

If you have any questions, please feel free to contact me at apobrien@wpi.edu.
*/

//#define TIME_DEBUG //comment this when connected to the instrument network

#include "InstrumentNetwork.h"

//these numbers will control pitch. They can be digital pin numbers, servo values, etc.
const int melodyData[10][4] ={
{0, 0, 0, 0},
{1, 1, 1, 1},
{2, 2, 2, 2},
{3, 3, 3, 3},
{4, 4, 4, 4},
{5, 5, 5, 5},
{6, 6, 6, 6},
{7, 7, 7, 7},
{8, 8, 8, 8},
{9, 9, 9, 9}};

//these numbers will control rhythm. They should be numbers in milliseconds.
const int rhythmData[10][4] ={
{375, 375, 375, 375},
{375, 375, 375, 375},
{375, 375, 375, 375},
{375, 375, 375, 375},
{375, 375, 375, 375},
{375, 375, 375, 375},
{375, 375, 375, 375},
{375, 375, 375, 375},
{375, 375, 375, 375},
{375, 375, 375, 375}};

void setup() {
	connectInstrument();
	//for your own testing:
	melody = 0; //can be 0-9
	rhythm = 0; //can be 0-9
}

void loop() {
	waitForBeat();
	playMeasure();
}

void playMeasure(){
	for(int i = 0; i < 4; i++){
		playPitch(melodyData[melody][i]);
		delay(rhythmData[rhythm][i]);
	}
}

void playPitch(int pitch){
	/* Do something to play a pitch such as:
	digitalWrite(pitch, HIGH);
	servo.write(pitch); */
}
