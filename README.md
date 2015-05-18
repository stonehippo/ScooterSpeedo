# ScooterSpeedo
A wheel encoder &amp; accelerometer speedometer for the tyke's scooter.

The tyke mentioned the other day that she'd like to know how fast she's going on her scooter. It occurred to me that I've got all of the parts laying around to make a kick-ass speedo for her, with some cool acceleration stuff built in.

## The accelerometer

I'm using an [Adafruit MMA8451 Accelerometer Breakout](http://www.adafruit.com/product/2019), a nifty, inexpensive little board that got +/-2/4/8G readings and uses I2C to communicate. This board is easy to use, thanks to Adafruit sensor library, and is simple to wire up, since it uses two-wire I2C protocol. Just hook up +5v, ground, connect SDA to pin A4, SCL to pin A5, and you're all set.
