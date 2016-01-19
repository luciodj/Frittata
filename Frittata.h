/*
  Firmata.h - Firmata library v2.5.1 - 2015-12-26
  Copyright (c) 2006-2008 Hans-Christoph Steiner.  All rights reserved.
  Copyright (C) 2009-2015 Jeff Hoefs.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#ifndef Firmata_h
#define Firmata_h

#include "boards.h"  /* Hardware Abstraction Layer */

/* Version numbers for the protocol.  The protocol is still changing, so these
 * version numbers are important.
 * Query using the REPORT_VERSION message.
 */
#define FIRMATA_PROTOCOL_MAJOR_VERSION  2 // for non-compatible changes
#define FIRMATA_PROTOCOL_MINOR_VERSION  5 // for backwards compatible changes
#define FIRMATA_PROTOCOL_BUGFIX_VERSION 1 // for bugfix releases

/* Version numbers for the Firmata library.
 * The firmware version will not always equal the protocol version going forward.
 * Query using the REPORT_FIRMWARE message.
 */
#define FIRMATA_FIRMWARE_MAJOR_VERSION  2
#define FIRMATA_FIRMWARE_MINOR_VERSION  5
#define FIRMATA_FIRMWARE_BUGFIX_VERSION 1

#define MAX_DATA_BYTES           64 // max number of data bytes in incoming messages

// message command bytes (128-255/0x80-0xFF)
#define DIGITAL_MESSAGE         0x90 // send data for a digital port (collection of 8 pins)
#define ANALOG_MESSAGE          0xE0 // send data for an analog pin (or PWM)
#define REPORT_ANALOG           0xC0 // enable analog input by pin #
#define REPORT_DIGITAL          0xD0 // enable digital input by port pair
//
#define SET_PIN_MODE            0xF4 // set a pin to INPUT/OUTPUT/PWM/etc
#define SET_DIGITAL_PIN_VALUE   0xF5 // set value of an individual digital pin
//
#define REPORT_VERSION          0xF9 // report protocol version
#define SYSTEM_RESET            0xFF // reset from MIDI
//
#define START_SYSEX             0xF0 // start a MIDI Sysex message
#define END_SYSEX               0xF7 // end a MIDI Sysex message

// extended command set using sysex (0-127/0x00-0x7F)
/* 0x00-0x0F reserved for user-defined commands */
#define SERIAL_MESSAGE          0x60 // communicate with serial devices, including other boards
#define ENCODER_DATA            0x61 // reply with encoders current positions
#define SERVO_CONFIG            0x70 // set max angle, minPulse, maxPulse, freq
#define STRING_DATA             0x71 // a string message with 14-bits per char
#define STEPPER_DATA            0x72 // control a stepper motor
#define ONEWIRE_DATA            0x73 // send an OneWire read/write/reset/select/skip/search request
#define SHIFT_DATA              0x75 // a bitstream to/from a shift register
#define I2C_REQUEST             0x76 // send an I2C read/write request
#define I2C_REPLY               0x77 // a reply to an I2C read request
#define I2C_CONFIG              0x78 // config I2C settings such as delay times and power pins
#define EXTENDED_ANALOG         0x6F // analog write (PWM, Servo, etc) to any pin
#define PIN_STATE_QUERY         0x6D // ask for a pin's current mode and value
#define PIN_STATE_RESPONSE      0x6E // reply with pin's current mode and value
#define CAPABILITY_QUERY        0x6B // ask for supported modes and resolution of all pins
#define CAPABILITY_RESPONSE     0x6C // reply with supported modes and resolution
#define ANALOG_MAPPING_QUERY    0x69 // ask for mapping of analog to pin numbers
#define ANALOG_MAPPING_RESPONSE 0x6A // reply with mapping info
#define REPORT_FIRMWARE         0x79 // report name and version of the firmware
#define SAMPLING_INTERVAL       0x7A // set the poll rate of the main loop
#define SCHEDULER_DATA          0x7B // send a createtask/deletetask/addtotask/schedule/querytasks/querytask request to the scheduler
#define SYSEX_NON_REALTIME      0x7E // MIDI Reserved for non-realtime messages
#define SYSEX_REALTIME          0x7F // MIDI Reserved for realtime messages
// these are DEPRECATED to make the naming more consistent
#define FIRMATA_STRING          0x71 // same as STRING_DATA
#define SYSEX_I2C_REQUEST       0x76 // same as I2C_REQUEST
#define SYSEX_I2C_REPLY         0x77 // same as I2C_REPLY
#define SYSEX_SAMPLING_INTERVAL 0x7A // same as SAMPLING_INTERVAL

// callback function types
typedef void (*callbackFunction)(uint8_t, int);
typedef void (*systemResetCallbackFunction)(void);
typedef void (*stringCallbackFunction)(char *);
typedef void (*sysexCallbackFunction)(uint8_t command, uint8_t argc, uint8_t *argv);

/* constructors */
void Firmata_initialize(void);
void Firmata_begin(void);

/* querying functions */
//void setFirmwareVersion(uint8_t major, uint8_t minor);  // see macro below
//void Firmata_setFirmwareNameAndVersion(const char *name, uint8_t major, uint8_t minor);

/* serial receive handling */
int Firmata_available(void);
void Firmata_processInput(void);

/* serial send handling */
void Firmata_sendAnalog(uint8_t pin, int value);
void Firmata_sendDigital(uint8_t pin, int value); // TODO implement this
void Firmata_sendDigitalPort(uint8_t portNumber, int portData);
void Firmata_sendString(const char *string);
void Firmata_sendCmdString(uint8_t command, const char *string);
void Firmata_sendSysex(uint8_t command, uint8_t bytec, uint8_t *bytev);
void Firmata_write(uint8_t c);

/* attach & detach callback functions to messages */
void Firmata_attach(uint8_t command, void* newFunction);
void Firmata_detach(uint8_t command);

/* firmware name and version */
//uint8_t firmwareVersionCount;
uint8_t firmwareVersionVector[2];

/* input message handling */
uint8_t waitForData;                // this flag says the next serial input will be data
uint8_t mbCmd;                      // execute this after getting multi-uint8_t data
uint8_t mbChn;                      // channel data for multiByteCommands
uint8_t inBuf[MAX_DATA_BYTES];      // multi-uint8_t data

/* sysex */
bool parsingSysex;
int sysexBytesRead;

/* private methods ------------------------------ */
void processSysexMessage(void);
void systemReset(void);
void strobeBlinkPin(uint8_t pin, int count);

/* callback functions */
void Callback( uint8_t cmd, uint8_t pin, int value);

//callbackFunction currentAnalogCallback;
//callbackFunction currentDigitalCallback;
//callbackFunction currentReportAnalogCallback;
//callbackFunction currentReportDigitalCallback;
//callbackFunction currentPinModeCallback;
//callbackFunction currentPinValueCallback;
//systemResetCallbackFunction currentSystemResetCallback;
//stringCallbackFunction currentStringCallback;
//sysexCallbackFunction currentSysexCallback;



/*==============================================================================
 * MACROS
 *============================================================================*/

/* shortcut for setFirmwareNameAndVersion() that uses __FILE__ to set the
 * firmware name.  It needs to be a macro so that __FILE__ is included in the
 * firmware source file rather than the library source file.
 */
//#define setFirmwareVersion(x, y)   setFirmwareNameAndVersion(__FILE__, x, y)

#endif /* Firmata_h */
