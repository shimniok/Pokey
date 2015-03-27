# Pokey

Pokey is the firefighting robot I entered into the 2007 Front Range Robotics Firefighting Challenge. It lost. But I've been
revising and improving it over the years.

I've also been using it to demonstrate robotics to lots and lots of children and quite a few adults at various robotics
expos like Robots At The Hangar, Denver Mini Maker Faire, and so on.  The kids love it. :)

# Directories

 * ff - is the main code base that I'm writing from scratch
 * encoders - scratch area for me playing with encoders
 * simple-test - is a simple led blinky, mostly for me playing
 * demo - some basic demonstration functionality, mostly for me playing

# Details

The basic Pokey Design uses a Pololu Orangutan LV168 with ATmega168 onboard. I'm using the old libpololu-avr library.

## Pinout

See LV168_Pinout.png

 * PC0 (PCINT8) - Right Encoder
 * PC1 (PCINT9) - Left Encoder

## Drivetrain

The robot has differential drive, using Tamiya 70168 Double Gearbox with low voltage Mabuchi motors.

## Chassis

The chassis is made of 1/4" funiture-grade plywood (or if I update it, hobby-grade plywood)

