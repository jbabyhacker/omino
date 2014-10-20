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

#define Sol1 4
#define Sol2 6
#define Sol3 5
#define Sol4 3
#define Sol5 7
#define Sol6 2

#include "InstrumentNetwork.h"

//these numbers will control pitch. They can be digital pin numbers, servo values, etc.
const int melodyData[10][4] ={
{2, 5, 6, 1},
{4, 1, 6, 5},
{1, 1, 1, 1},
{5, 4, 3, 2},
{6, 2, 5, 1},
{1, 2, 3, 4},
{4, 2, 4, 5},
{5, 1, 1, 3},
{4, 2, 1, 6},
{1, 1, 1, 1}};

//these numbers will control rhythm. They should be numbers in milliseconds.
const int rhythmData[10][4] ={
{375, 375, 375, 375},
{500, 500, 0, 500},
{0, 0, 750, 750},
{150, 250, 900, 200},
{375, 0, 500, 625},
{500, 500, 250, 250},
{150, 600, 150, 600},
{600, 150, 600, 150},
{150, 150, 150, 1050},
{750, 0, 750, 0}};

void setup() {
	connectInstrument();

        pinMode(Sol1, OUTPUT);
        pinMode(Sol2, OUTPUT);
        pinMode(Sol3, OUTPUT);
        pinMode(Sol4, OUTPUT);
        pinMode(Sol5, OUTPUT);
        pinMode(Sol6, OUTPUT);
        
        /*attachInterrupt(Sol1, ISR1, (!LOW));
        attachInterrupt(Sol2, ISR2, (!LOW));
        attachInterrupt(Sol3, ISR3, (!LOW));
        attachInterrupt(Sol4, ISR4, (!LOW));
        attachInterrupt(Sol5, ISR5, (!LOW));
        attachInterrupt(Sol6, ISR6, (!LOW));*/

	//for your own testing:
	/*melody = 7; //can be 0-9
	rhythm = 7; //can be 0-9*/
}

void loop() {
	waitForBeat();
	playMeasure();
}

void playMeasure(){
	for(int i = 0; i < 4; i++){
		playPitch(melodyData[melody][i]);
                while (rhythmData[rhythm][i] == 0)
                {
                 i++;
                playPitch(melodyData[melody][i]); //allows instrument to play multiple notes
                //at once. Only problem is that rhythm and melody are separate.
                }
                delay(125);
                digitalWrite(Sol1, LOW);
                digitalWrite(Sol2, LOW);
                digitalWrite(Sol3, LOW);
                digitalWrite(Sol4, LOW);
                digitalWrite(Sol5, LOW);
                digitalWrite(Sol6, LOW);
		delay((rhythmData[rhythm][i])-125);
	}
}

void playPitch(int pitch){
	/* Do something to play a pitch such as:
	digitalWrite(pitch, HIGH);
	servo.write(pitch); */
  if (pitch == 1)
  {
    digitalWrite(Sol1, HIGH);
  }
  else if (pitch == 2)
  {
    digitalWrite(Sol2, HIGH);
  }
  else if (pitch == 3)
  {
    digitalWrite(Sol3, HIGH);
  }
  else if (pitch == 4)
  {
    digitalWrite(Sol4, HIGH);
  }
  else if (pitch == 5)
  {
    digitalWrite(Sol5, HIGH);
  }
  else if (pitch == 6)
  {
    digitalWrite(Sol6, HIGH);
  }
}

/*void ISR1()
{
 int q = 0;
  while (q < 100)
 {
  q++;
 } 
 digitalWrite(Sol1, LOW);
}

void ISR2()
{
 int q = 0;
  while (q < 100)
 {
  q++;
 } 
 digitalWrite(Sol2, LOW);
}

void ISR3()
{
 int q = 0;
  while (q < 100)
 {
  q++;
 } 
 digitalWrite(Sol3, LOW);
}

void ISR4()
{
 int q = 0;
  while (q < 100)
 {
  q++;
 } 
 digitalWrite(Sol4, LOW);
}

void ISR5()
{
 int q = 0;
  while (q < 100)
 {
  q++;
 } 
 digitalWrite(Sol5, LOW);
}

void ISR6()
{
 int q = 0;
  while (q < 100)
 {
  q++;
 } 
 digitalWrite(Sol6, LOW);
}*/
