/*
 Boards.h - Hardware Abstraction Layer for Frittata library
  
 Copyright(c) 2016 Lucio Di Jasio. All rights reserved.
  
 Based on the original Firmata project by Hans-Christoph Steiner and Jeff Hoefs.  

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#ifndef Firmata_Boards_h
#define Firmata_Boards_h

Xpress  // for digitalRead, digitalWrite, etc

/*
    Firmata Hardware Abstraction Layer

Firmata is built on top of the hardware abstraction functions of Arduino,
specifically digitalWrite, digitalRead, analogWrite, analogRead, and
pinMode.  While these functions offer simple integer pin numbers, Firmata
needs more information than is provided by Arduino.  This file provides
all other hardware specific details.  To make Firmata support a new board,
only this file should require editing.

The key concept is every "pin" implemented by Firmata may be mapped to
any pin as implemented by Arduino.  Usually a simple 1-to-1 mapping is
best, but such mapping should not be assumed.  This hardware abstraction
layer allows Firmata to implement any number of pins which map onto the
Arduino implemented pins in almost any arbitrary way.


General Constants:

These constants provide basic information Firmata requires.

TOTAL_PINS: The total number of pins Firmata implemented by Firmata.
    Usually this will match the number of pins the Arduino functions
    implement, including any pins pins capable of analog or digital.
    However, Firmata may implement any number of pins.  For example,
    on Arduino Mini with 8 analog inputs, 6 of these may be used
    for digital functions, and 2 are analog only.  On such boards,
    Firmata can implement more pins than Arduino's pinMode()
    function, in order to accommodate those special pins.  The
    Firmata protocol supports a maximum of 128 pins, so this
    constant must not exceed 128.

TOTAL_ANALOG_PINS: The total number of analog input pins implemented.
    The Firmata protocol allows up to 16 analog inputs, accessed
    using offsets 0 to 15.  Because Firmata presents the analog
    inputs using different offsets than the actual pin numbers
    (a legacy of Arduino's analogRead function, and the way the
    analog input capable pins are physically labeled on all
    Arduino boards), the total number of analog input signals
    must be specified.  16 is the maximum.

VERSION_BLINK_PIN: When Firmata starts up, it will blink the version
    number.  This constant is the Arduino pin number where a
    LED is connected.


Pin Mapping Macros:

These macros provide the mapping between pins as implemented by
Firmata protocol and the actual pin numbers used by the Arduino
functions.  Even though such mappings are often simple, pin
numbers received by Firmata protocol should always be used as
input to these macros, and the result of the macro should be
used with with any Arduino function.

When Firmata is extended to support a new pin mode or feature,
a pair of macros should be added and used for all hardware
access.  For simple 1:1 mapping, these macros add no actual
overhead, yet their consistent use allows source code which
uses them consistently to be easily adapted to all other boards
with different requirements.

IS_PIN_XXXX(pin): The IS_PIN macros resolve to true or non-zero
    if a pin as implemented by Firmata corresponds to a pin
    that actually implements the named feature.

PIN_TO_XXXX(pin): The PIN_TO macros translate pin numbers as
    implemented by Firmata to the pin numbers needed as inputs
    to the Arduino functions.  The corresponding IS_PIN macro
    should always be tested before using a PIN_TO macro, so
    these macros only need to handle valid Firmata pin
    numbers for the named feature.


Port Access Inline Funtions:

For efficiency, Firmata protocol provides access to digital
input and output pins grouped by 8 bit ports.  When these
groups of 8 correspond to actual 8 bit ports as implemented
by the hardware, these inline functions can provide high
speed direct port access.  Otherwise, a default implementation
using 8 calls to digitalWrite or digitalRead is used.

When porting Firmata to a new board, it is recommended to
use the default functions first and focus only on the constants
and macros above.  When those are working, if optimized port
access is desired, these inline functions may be extended.
The recommended approach defines a symbol indicating which
optimization to use, and then conditional complication is
used within these functions.

readPort(port, bitmask):  Read an 8 bit port, returning the value.
   port:    The port number, Firmata pins port*8 to port*8+7
   bitmask: The actual pins to read, indicated by 1 bits.

writePort(port, value, bitmask):  Write an 8 bit port.
   port:    The port number, Firmata pins port*8 to port*8+7
   value:   The 8 bit value to write
   bitmask: The actual pins to write, indicated by 1 bits.
*/

/*==============================================================================
 * Board Specific Configuration
 *============================================================================*/

#ifndef digitalPinHasPWM
#define digitalPinHasPWM(p)     IS_PIN_DIGITAL(p)
#endif

#if defined(XPRESS_18855)
#define TOTAL_ANALOG_PINS       22
#define TOTAL_PINS              22
#define VERSION_BLINK_PIN       LED_BUILTIN
#define PIN_SERIAL1_RX          16+1    // RC1 RX-USB
#define PIN_SERIAL1_TX          16+0    // RC0 TX-USB
#define IS_PIN_DIGITAL(p)       true
#define IS_PIN_ANALOG(p)        true
#define IS_PIN_PWM(p)           true
#define IS_PIN_SERVO(p)         true
#define IS_PIN_I2C(p)           ((p) == SCL || (p) == SDA)
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK)
#define IS_PIN_SERIAL(p)        ((p) == 13 || (p) == 14)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        (p)
#define PIN_TO_PWM(p)           (p)
#define PIN_TO_SERVO(p)         (p)
// anything else
#else
#error "Please edit Boards.h with a hardware abstraction for this board"
#endif

// as long this is not defined for all boards:
#ifndef IS_PIN_SPI
#define IS_PIN_SPI(p)           0
#endif

#ifndef IS_PIN_SERIAL
#define IS_PIN_SERIAL(p)        0
#endif


/*==============================================================================
 * readPort() - Read an 8 bit port
 *============================================================================*/
#endif /* Firmata_Boards_h */
