/*
 Boards.h - Hardware Abstraction Layer for Frittata library
  
 Author: Lucio Di Jasio
  
 Based on the original Firmata project by Hans-Christoph Steiner and Jeff Hoefs.  

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#ifndef Firmata_Boards_h
#define Firmata_Boards_h

#include "Xpress.h"  // for digitalRead, digitalWrite, etc

/*
    Frittata Hardware Abstraction Layer

Frittata is built on top of the hardware abstraction functions of Xpress,
specifically digitalWrite, digitalRead, analogWrite, analogRead, and
pinMode.  While these functions offer simple integer pin numbers, Frittata
needs more information.  This file provides all other hardware specific details.  
To make Frittata support a new board, only this file should require editing.

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

#endif /* Firmata_Boards_h */
