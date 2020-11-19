#include <RGBcontrol.h>
RGBControl RGBLED(3,5,6,activeHigh);
//Note : USE PWM PINS (e.g. 3,5,6)
int currentMode;
int modeTime=3000; //3000ms per Mode

/*
This script provides a very simple example how to use the millis function in Arduino to
do timespans without stalling the µC with an delay command. Note how the current mode
is selected using millis()/modeTime % 6.
The modulo operator % subtracts the first expression by 6 until the remain is less than 6.
So our current mode can contain values from 0-5 which are used by the switch statement below.
*/

void setup() {
RGBLED.init();
}

void loop() {
 currentMode = (millis()/modeTime) % 6;
 switch (currentMode){
  case 0:
    RGBLED.HSL_Fade(20,50);
  break;
  case 1:
    RGBLED.HSL_Hard_Fade(500,6,50);
  break;
  case 2:
    RGBLED.HSL_Hard_Fade(100,3,50);
  break;
  case 3:
    /*
    This if-else condition below uses the same function as the currentMode to generate a stroboscope
    effect while currentMode = 3
    */
    if((millis()/50)%2) RGBLED.HSL(0,100);
    else RGBLED.HSL(0,0);
  break;
  case 4:
    RGBLED.HSL_Blink(500,1500,400,60);
  break;
  case 5:
    RGBLED.HSL_Blink(500,1000,0,220);
  break;      
  }
}
