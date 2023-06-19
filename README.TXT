This is a super simple voltage sensor for the FRSKY s.port protocol.

I personally build these using a little DFRobot Beetle.. but any arduino will work.

https://www.dfrobot.com/product-1075.html?tracking=IxcGjYvhlD7rPBQdORDufaZKAdHm4J1TEGZibroDLQF8rHGWdRylNEqRFkyyCqco

Required are:

- beetle/arduino
- 2.2K resistor
- 10K resistor

The aim is to simply set the voltage divider to output onto the analog port - result is a nice low voltage for arduino to read and return the data.

Please not the code returns 'whole numbers'.

So for 8.5v you will receive 850

You can simply multiply this out on the radio to get the decimal to move.