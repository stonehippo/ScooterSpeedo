# ScooterSpeedo
A wheel encoder &amp; accelerometer speedometer for the tyke's scooter.

The tyke mentioned the other day that she'd like to know how fast she's going on her scooter. It occurred to me that I've got all of the parts laying around to make a kick-ass speedo for her, with some cool acceleration stuff built in.

## The microcontroller

I happen to have a few Arduinos laying around<a href="#fn1"><sup>1</sup></a>, so I'm turning to those. For this project, I'm using an Arduino Pro Mini 5v. I chose the smallest Arduino-compatible I've got onhand to keep the size and weight down on the scooter-mounted components.

## The accelerometer

I'm using an [Adafruit MMA8451 Accelerometer Breakout](http://www.adafruit.com/product/2019), a nifty, inexpensive little board that has +/-2/4/8G readings and uses I2C to communicate. This board is easy to use, thanks to Adafruit sensor library, and is simple to wire up, since it uses two-wire I2C protocol. Just hook up +5v, ground, connect SDA to pin A4, SCL to pin A5, and you're all set.

## The display

I'm using a standard 16X2 LCD display for showing information from the sensors. The LCD backlight and contrast levels are connected to PWM pins on the Arduino, so the board can set the levels directly (rather than hooking them up to a potentiometer or something).

-----

1. <a name="fn1"></a> It's more like I've grabbed a bunch of Arduinos and clones in various form factors that past couple of Arduino days! And now I need to start integrating them into projects. Like this one. :)
