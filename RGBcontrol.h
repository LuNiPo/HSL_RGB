
/*
  RGBcontroll.cpp - Library for controlling RGB_LEDs using HSL values.
  Created by Lukas N. Possenig, November 10, 2020.
  Released into the public domain.
*/
#ifndef ledcontrol_h
#define ledcontrol_h
#include <Arduino.h>

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
	#define MAXPWM 255
#else
	#define MAXPWM 1023
#endif 

enum outputType {activeLow=1 , activeHigh=-1};


class RGBControl{
public:
	RGBControl(byte redPin,byte greenPin,byte bluePin, outputType inv);
	void init();
	void HSL(int hue, int lighness);
	void HSL_Fade(int speed, int lightness);
	void HSL_Area_Fade(int speed,int startAngle,int fadeAngle,int lightness);
	void HSL_Hard_Fade(int speed,int numberOfColors, int lightness);
	void HSL_Blink(int onTime, int periodTime, int fadeTime, int Hue);
	void RGB(int red,int green,int blue);

private:
	int hueMap (int hue); // map Hue to PWM
	void update(); //update PWM Outputs
	int _colorPwmValues[3];
	byte _rgbPin[3];
	int _invertOutput;
};

#endif
