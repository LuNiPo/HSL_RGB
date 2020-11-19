## HSL_RGB
### Just another Arduino Libary ? - Asyncronous RGB LED Controlling using HSL Color values

This is me getting my Hands down on (RGB) LED controlling. After i studied some already existing Libarys i figured out some things :
* Many of them are very unflexible with generating Colors or fading the lightness (or the Light intenisty)
* Most of them using delay() functions for animations, which is bad if you want your microcontroller to do more than just blinking some stupid LEDs

so for my new Project there was a need for a different Approach.

---
### How does it work ?
My approach was to use HSL Colors (Hue Saturation Lightness), honestly this name isnt quite right, since you cant make gray light... anyway
the HSL Color sceme uses some simple trick. It uses an cylindrical shape to display all colors (see picture below)
![alt text](https://upload.wikimedia.org/wikipedia/commons/6/6b/HSL_color_solid_cylinder_saturation_gray.png "Logo Title Text 1")
as i've statet we can't generate gray light, therefore only the hull of the cylinder is used in this case. Therefore all we need are the Hue and Lightness value.Hue is a degree value from 0 to 360 where 
* 0 is Red Light
* 120 is Green Light
* 240 is Blue Light
* Hue > 360 = Hue - 360

Lightness is the vertical position on the hull (from black to white). Since we are also not able to generate Black light the lightness value uses following rules:
* **0 <= lightness <50** Do PWM on the outputs to reduce lightintensity (keep proportion of the pwm signals)
* **lightness = 50** full color (PWM on the outputs matches the calculated values)
* **50<lightness<=100** fade to white (increase pwm on all channels until they're 1024)
### Asyncronous ? - Kind of ... i guess
instead of delays for generating animation I used the millis() function - a quiet common trick nowadays to do delays without stalling your µC. You can see the idea in one of the Example script. A downside is that you cant use delay() in your script without stalling the animation. Anyways - cause we not using delay you can do things like start stop animations by the push of an button - **at any time!**

---
### Thats nice! but how do i use it ?
A few simple steps:
* Include the libary `#include <RGBControl.h>`
* Set up an Controller Object `RGBControl Controller(red pin, green pin, blue pin, activeHigh/activeLow)` **_Note:_** activeHigh/ activeLow defines the usage of your output: **Your LED lights up when your pin is high ? - use activeHigh**
* Use a few predefiened functions like:
  * `Controller.HSL(colorAngle, lightness)` For displaying single colors
  * `Controller.HSL_Fade(speed, lightness)` For fading throught the whole spectrum. _(won't work with delay())_
  * `Controller.HSL_Area_Fade(speed,Angle,fadeAngle,lightness)` Fades between 2 Colors. _(won't work with delay())_
  * `Controller.HSL_Hard_Fade(timePerColor,numberOfColors,lightness)` Fades through whole spectrum using predefined number of Steps. _(maybe works with delay() when timePerColor > delay()_
  * `Controller.HSL_Blink(onTime, periodTime, transisionTime, Color)` Do sum blinking - and be able to do some fading from off to on. Transision time is added o the off time period therefor periode time must be > 2 * transisionTime + onTime _(will maybe work with delays() when no transision time is used and period time is bigger than delay())_
  * `Controller.RGB(red,green,blue)` classical way of setting RGB values in percent (0-100) - like why not since we've already an controller object.
---
### How to include?

* Click on the **green code button** on top -> download as .zip file
* Open your arduino IDE choose **Sketch -> IncludeLibary -> Add Zip libary**
* Choose the zip file and include it
* Open on of the example scripts

---
Image source :
HSL_color_solid_cylinder.png: SharkD derivative work: SharkD Talk (https://commons.wikimedia.org/wiki/File:HSL_color_solid_cylinder_saturation_gray.png), „HSL color solid cylinder saturation gray“, https://creativecommons.org/licenses/by-sa/3.0/legalcode 
