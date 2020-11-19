/*
  RGBcontroll.cpp - Library for controlling RGB_LEDs using HSL values.
  Created by Lukas Possenig, November 10, 2020.
  Released into the public domain.
*/
#include "RGBcontrol.h"
#include <Arduino.h>

RGBControl::RGBControl(byte redPin,byte greenPin,byte bluePin, outputType inv){
	this ->_rgbPin[0] = redPin;
	this ->_rgbPin[1] = greenPin;
	this ->_rgbPin[2] = bluePin;
	this ->_invertOutput=inv;
}
void RGBControl::init(){
for(int i=0;i<3;i++){
	pinMode(_rgbPin[i],OUTPUT);
}
}
//Main Function - generates an array of 3 PWM values from the input hue an lightness
void RGBControl::HSL(int hue, int lightness){

	for(int i=0;i<3;i++){
		_colorPwmValues[i]=hueMap(hue + 120*i);	
		if (lightness<=50) _colorPwmValues[i] = _colorPwmValues[i] * lightness/50;
		else _colorPwmValues[i] += (MAXPWM-_colorPwmValues[i])*(lightness-50)/50;
	}
	update();
}

/*
Decoding the PWM Values from hue Angle. Since red is at 0°, green is at 120° and
blue is at 240° you need to offset the hue value when calling to decode the 3 seperate channels.
*/
int RGBControl::hueMap (int angle){
	int value;
	if(angle >= 361) angle -=360;  //periodic for angle > 2pi
	if(angle <=  60) value = MAXPWM;
	else if (angle <=120) value = 1023 - (angle-60)*MAXPWM/60;
	else if (angle <=240) value = 0;
	else if (angle <=300) value = (angle-240)*17.05;
	else if (angle <=360) value = MAXPWM;
	return value;	
}

//Update Outputs with calculated PWM Values 
void RGBControl::update(){
	for(int i=0;i<3;i++){
		_colorPwmValues[i] = MAXPWM * ( _invertOutput + 1)/2 - _colorPwmValues[i]*_invertOutput; 
		analogWrite(_rgbPin[i],_colorPwmValues[i]);
	}
}

//generates an continous fading.
void RGBControl::HSL_Fade(int speed, int lightness){
	HSL((millis()/(speed+1))%361,lightness);
}

/*
Generates Fading between 2 Colors. startAngle defines themiddle of the fading area. therefor
minAngle = startAngle - fadeAngle / 2
maxAngle = startAngle + fadeAngle / 2
*/
void RGBControl::HSL_Area_Fade(int speed,int startAngle,int fadeAngle,int lightness){
	HSL(abs((millis()/(speed+1)) % fadeAngle -fadeAngle/2) + startAngle,lightness);
}

/*
Display an preset amount of different Colors evenly spread around the Circle speed defindes the ms per color
*/
void RGBControl::HSL_Hard_Fade(int speed,int numberOfColors, int lightness){
	HSL(((millis()/(speed+1)) % numberOfColors)*360/numberOfColors,lightness);
}

/*
Function for dooing Blinking with on-off fading. Fade time is added to the off Time therfore let period time be
periodTime > fadeTime * 2 + onTime.
Use fadeTime=0 for normal blinking.
Times are ms values.
*/
void RGBControl::HSL_Blink(int onTime, int periodTime, int fadeTime, int Hue){
	int deltaTime = millis() % periodTime ;
	if(deltaTime < fadeTime) HSL(Hue,deltaTime * 50/fadeTime);
	else if(deltaTime < fadeTime + onTime) HSL(Hue,50);
	else if(deltaTime < 2 * fadeTime + onTime) HSL(Hue, 50 - ( deltaTime -(fadeTime + onTime))*50/fadeTime);
	else HSL(Hue,0);
}

/*
Function for setting the Color using RGB percentages - why not, since we already implementet the RGB Object.
Maybe also helps when you switch between different Microcrontrollers since Arduino Uno uses 0-255 for PWM, 
ESP uses 0-1023.   
*/
void RGBControl::RGB(int red,int green,int blue){
	_colorPwmValues[0]=red * MAXPWM / 100;
	_colorPwmValues[1]=green * MAXPWM / 100;
	_colorPwmValues[2]=blue * MAXPWM / 100;
	update();
}

