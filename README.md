## HSL_RGB
### Just another Arduino Libary

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

Lighness is the height on the hull (from black to white). Since we are also not able to generate Black light the lightness value uses following rules:
* **0 <= lightness <50** Do PWM on the outputs to reduce lightintensity (keep proportion of the pwm signals)
* **lightness = 50** full color (PWM on the outputs matches the calculated values)
* **50<lightness<=100** fade to white (increase pwm on all channels until they're 1024)
---
Image source :
HSL_color_solid_cylinder.png: SharkD derivative work: SharkD Talk (https://commons.wikimedia.org/wiki/File:HSL_color_solid_cylinder_saturation_gray.png), „HSL color solid cylinder saturation gray“, https://creativecommons.org/licenses/by-sa/3.0/legalcode 