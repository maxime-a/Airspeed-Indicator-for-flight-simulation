# Airspeed-Indicator-for-flight-simulation

Analog airspeed indicator for flight simulation with servo and 3d print.

## Hardware

I use an arduino uno with a servo motor driving a gear with a multiplication of 2.66. I need multiplication because servo can only turn from 0 to 180 degrees and the airspeed indicator need 360 degrees. For the structure and gears i use the files from alvaroalea : https://www.thingiverse.com/thing:2489322 . I just replaced the 3d printed axis by a metal axis.

## Software

To extract data from the flight simulator i use a software named Link2Fs from : http://www.jimspage.co.nz/intro.htm , it is very easy to extract the airspeed and transmit it via the serial connection to the arduino which control the servo. The fonction to drive the angle of the servo from the indicated airspeed is made of 2 linear regression to approximate the real gauge.
This is the code i use based on an exemple from the software.

![Multi_Keys_with_flaps_servo.ino](\Multi_Keys_with_flaps_servo.ino)
