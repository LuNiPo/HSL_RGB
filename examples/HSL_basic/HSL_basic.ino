#include <RGBcontrol.h>
/*
IMPORTANT: DONT USE delay() WITH THIS LIBARY SINCE IT WILL STALL ANIMATIONS 
(fading blinking etc.) 
Display Static colors will work fine though.


Set up an RGB Controller Object called RGBLED on PWM
Pins 3,5,6 (Arduino UNO) 

Usage : RGBControl [Name](RED LED, GREEN LED, BLUE LED, activeLow /activeHigh)
Note: invert output state with activeLow/High:
LED lights up when output is low - activeLow
Led lights up wehn output is hight - activeHight
*/
RGBControl RGBLED(3,5,6,activeHigh);


void setup() {
/*
Initialize those pins as Outputs, could be done the
classic way.
*/
RGBLED.init();
}

void loop() {
/*
Different Modes for the RGB LED Object 
Uncomment them one at a Time
*/
  
  /*
  Displays a single color using HSL Values. Usage:
  [Name].HSL(Color,lightness);
  where the Color is 0-360 (0,360 Red, 120 Green, 249 Blue)
  lighness is a value from 0 to 100 where
  0 = off, 50 means full Color, 100 = white light.
  */
//RGBLED.HSL(120,50);

  /*
  Fading though the whole colorrange. 
  [Name].HSL_Fade(Speed,lightness);
  */
RGBLED.HSL_Fade(30,50);

  /*
  Fading between 2 Colors. 
  [Name].HSL_Area_Fade(Speed,Angle,fade Angle,lightness);
  NOTE: Area is Angle +- fadeAngle/2.
  */
//RGBLED.HSL_Area_Fade(30,0,120,50);

  /*
  Jumbing between n colors. 
  [Name].HSL_hard_Fade(Speed (time per color in ms) ,number of Colors (0-360),lightness);
  NOTE: Area is Angle +- fadeAngle/2.
  */
//RGBLED.HSL_Hard_Fade(500,6,50);

  /*
  Blinking (with soft transisions). 
  [Name].HSL_Blink(on Time, period Time, transision Time, Color angle);
  NOTE: Transision is executet in off time therefore period time must be greather than
  2*transision Time + on Time. Set transision Time 0 for normal on/off blinking.
  */
//RGBLED.HSL_Blink(1000,2000,300,240);

  /*
  Setting the color using plain old RGB percentages (0-100);
  */
//RGBLED.RGB(100,0,100);
}
