# ScooterSpeedo
A wheel encoder &amp; accelerometer speedometer for the tyke's scooter.

The tyke mentioned the other day that she'd like to know how fast she's going on her scooter. It occurred to me that I've got all of the parts laying around to make a kick-ass speedo for her, with some cool acceleration stuff built in.

## Compenents

* [Arduino Pro Mini 5v 16mHz](https://www.sparkfun.com/products/11113)
* [Adafruit MMA8451 3-axis 14-bit acceleroemeter](https://www.adafruit.com/products/2019)
* [Hall effect sensor](https://www.adafruit.com/product/158)
* [Magnet](https://www.adafruit.com/products/9)
* 16x2 LCD character display (I had a spare one around, more or less like [this LCD display](https://www.adafruit.com/products/181))
* 3D-printed speedometer case
* 3d-printed sensor bracket


## The microcontroller

I happen to have a few Arduinos laying around<a href="#fn1"><sup>1</sup></a>, so I'm turning to those. For this project, I'm using an Arduino Pro Mini 5v. I chose the smallest Arduino-compatible I've got on hand to keep the size and weight down on the scooter-mounted components.

## Speed sensor

The speed sensor is a Hall effect sensor paired with a high-strenght magnet. The magnet is mounted on the wheel and the sensor is mounted on a bracket attached to the frame of the scooter. This is pretty much the same as a standard bike speedometer.

Each time the wheel passes the sensor, the sensor is brought to 0V/ground and that fires an interrupt in the Arduino, which captures the time and a count of the number of ticks. The count is kept because we check calculate the speed in the Arduino loop, which includes a delay, and it's possible to miss an interrupt below calculations.

## The accelerometer

I'm using an [Adafruit MMA8451 Accelerometer Breakout](http://www.adafruit.com/product/2019), a nifty, inexpensive little board that has +/-2/4/8G readings and uses I2C to communicate. This board is easy to use, thanks to Adafruit sensor library, and is simple to wire up, since it uses two-wire I2C protocol. Just hook up +5v, ground, connect SDA to pin A4, SCL to pin A5, and you're all set.

## The display

I'm using a standard 16X2 LCD display for showing information from the sensors. The LCD backlight and contrast levels are connected to PWM pins on the Arduino, so the board can set the levels directly (rather than hooking them up to a potentiometer or something).

-----

1. <a name="fn1"></a> It's more like I've grabbed a bunch of Arduinos and clones in various form factors the past couple of Arduino days! And now I need to start integrating them into projects. Like this one. :)
