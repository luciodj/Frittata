/*
  Firmata.cpp - Firmata library v2.5.1 - 2015-12-26
  Copyright (c) 2006-2008 Hans-Christoph Steiner.  All rights reserved.
  Copyright (C) 2009-2015 Jeff Hoefs.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

//******************************************************************************
//* Includes
//******************************************************************************

#include "Frittata.h"
#include "mcc_generated_files/mcc.h"
#include <string.h>


//******************************************************************************
//* Support Functions
//******************************************************************************

void sendValueAsTwo7bitBytes(int value)
{
  putch((char)(value & 0x7f));      // LSB
  putch((char)(value >> 7 & 0x7f)); // MSB
}

void startSysex(void)
{
  putch(START_SYSEX);
}

void endSysex(void)
{
  putch(END_SYSEX);
}

// output the protocol version message to the serial port
void printVersion(void)
{
  putch(REPORT_VERSION);
  putch(FIRMATA_PROTOCOL_MAJOR_VERSION);
  putch(FIRMATA_PROTOCOL_MINOR_VERSION);
}

void blinkVersion(void)
{
#if defined(VERSION_BLINK_PIN)
  // flash the pin with the protocol version
  pinMode(VERSION_BLINK_PIN, OUTPUT);
  strobeBlinkPin(VERSION_BLINK_PIN, FIRMATA_FIRMWARE_MAJOR_VERSION);
  delay(250);
  strobeBlinkPin(VERSION_BLINK_PIN, FIRMATA_FIRMWARE_MINOR_VERSION);
  delay(125);
#endif
}

void printFirmwareVersion(void)
{
//  uint8_t i;
//  if (firmwareVersionCount) 
  { // make sure that the name has been set before reporting
    startSysex();
    putch(REPORT_FIRMWARE);
    putch(firmwareVersionVector[0]); // major version number
    putch(firmwareVersionVector[1]); // minor version number
//    for (i = 2; i < firmwareVersionCount; ++i) {
//      sendValueAsTwo7bitBytes(firmwareVersionVector[i]);
//    }
    endSysex();
  }
}
//******************************************************************************
//* Constructors
//******************************************************************************

void Firmata_initialize(void)
{
//  firmwareVersionCount = 0;
//  firmwareVersionVector = 0;
  systemReset();
}

//******************************************************************************
//* Public Methods
//******************************************************************************

/* begin method for overriding default serial bitrate */
void Firmata_begin(void)
{
//  Serial.begin(speed);    // always use default 57.600
//  FirmataStream = &Serial;
//  blinkVersion();
  printVersion();
  printFirmwareVersion();
}

/* begin method for overriding default stream */
//void begin(Stream &s)
//{
//  FirmataStream = &s;
//  // do not call blinkVersion() here because some hardware such as the
//  // Ethernet shield use pin 13
//  printVersion();
//  printFirmwareVersion();
//}


//void setFirmwareNameAndVersion(const char *name, uint8_t major, uint8_t minor)
//{
//  const char *firmwareName;
//  const char *extension;
//
//  // parse out ".cpp" and "applet/" that comes from using __FILE__
//  extension = strstr(name, ".cpp");
//  firmwareName = strrchr(name, '/');
//
//  if (!firmwareName) {
//    // windows
//    firmwareName = strrchr(name, '\\');
//  }
//  if (!firmwareName) {
//    // user passed firmware name
//    firmwareName = name;
//  } else {
//    firmwareName ++;
//  }
//
//  if (!extension) {
//    firmwareVersionCount = strlen(firmwareName) + 2;
//  } else {
//    firmwareVersionCount = extension - firmwareName + 2;
//  }
//
//  // in case anyone calls setFirmwareNameAndVersion more than once
////  free(firmwareVersionVector);
//
////  firmwareVersionVector = (uint8_t *) malloc(firmwareVersionCount + 1);
//  firmwareVersionVector[firmwareVersionCount] = 0;
//  firmwareVersionVector[0] = major;
//  firmwareVersionVector[1] = minor;
//  strncpy((char *)firmwareVersionVector + 2, firmwareName, firmwareVersionCount - 2);
//}

//------------------------------------------------------------------------------
// Serial Receive Handling

int Firmata_available(void)
{
  return Serial_DataReady();
}

void processSysexMessage(void)
{
  switch (inBuf[0]) { //first uint8_t in buffer is command
    case REPORT_FIRMWARE:
      printFirmwareVersion();
      break;
    case STRING_DATA:
//      if (currentStringCallback) {
//        uint8_t bufferLength = (sysexBytesRead - 1) / 2;
//        uint8_t i = 1;
//        uint8_t j = 0;
//        while (j < bufferLength) {
//          // The string length will only be at most half the size of the
//          // stored input buffer so we can decode the string within the buffer.
//          inBuf[j] = inBuf[i];
//          i++;
//          inBuf[j] += (inBuf[i] << 7);
//          i++;
//          j++;
//        }
//        // Make sure string is null terminated. This may be the case for data
//        // coming from client libraries in languages that don't null terminate
//        // strings.
//        if (inBuf[j - 1] != '\0') {
//          inBuf[j] = '\0';
//        }
//        (*currentStringCallback)((char *)&inBuf[0]);
//      }
      break;
    default:
//      if (currentSysexCallback)
//        (*currentSysexCallback)(inBuf[0], sysexBytesRead - 1, inBuf + 1);
        break;
  }
}

void Firmata_processInput(void)
{
  int inputData = EUSART_Read(); // this is 'int' to handle -1 when no data
  int command;

  if (parsingSysex) {
    if (inputData == END_SYSEX) {
      //stop sysex uint8_t
      parsingSysex = false;
      //fire off handler function
      processSysexMessage();
    } else {
      //normal data uint8_t - add to buffer
      inBuf[sysexBytesRead] = inputData;
      sysexBytesRead++;
    }
  } else if ( (waitForData > 0) && (inputData < 128) ) {
    waitForData--;
    inBuf[waitForData] = inputData;
    if ( (waitForData == 0) && mbCmd ) { // got the whole message  
        
        switch (mbCmd) {
        case ANALOG_MESSAGE:
            Callback(mbCmd, mbChn, (inBuf[0] << 7)+ inBuf[1]);
          break;
        case DIGITAL_MESSAGE:
            Callback(mbCmd, mbChn, (inBuf[0] << 7) + inBuf[1]);
          break;
        case SET_PIN_MODE:
            Callback(mbCmd, inBuf[1], inBuf[0]);
          break;
        case SET_DIGITAL_PIN_VALUE:
            Callback(mbCmd, inBuf[1], inBuf[0]);
          break;
        case REPORT_ANALOG:
            Callback(mbCmd, mbChn, inBuf[0]);
          break;
        case REPORT_DIGITAL:
            Callback(mbCmd, mbChn, inBuf[0]);
          break;
        default:
            break;                
      }
      mbCmd = 0;
    }
  } else {
    // remove channel info from command uint8_t if less than 0xF0
    if (inputData < 0xF0) {
      command = inputData & 0xF0;
      mbChn = inputData & 0x0F;
    } else {
      command = inputData;
      // commands in the 0xF* range don't use channel data
    }
    switch (command) {
      case ANALOG_MESSAGE:
      case DIGITAL_MESSAGE:
      case SET_PIN_MODE:
      case SET_DIGITAL_PIN_VALUE:
        waitForData = 2; // two data bytes needed
        mbCmd = command;
        break;
      case REPORT_ANALOG:
      case REPORT_DIGITAL:
        waitForData = 1; // one data uint8_t needed
        mbCmd = command;
        break;
      case START_SYSEX:
        parsingSysex = true;
        sysexBytesRead = 0;
        break;
      case SYSTEM_RESET:
        systemReset();
        break;
      case REPORT_VERSION:
        printVersion();
        break;
    }
  }
}

//------------------------------------------------------------------------------
// Serial Send Handling

// send an analog message
void Firmata_sendAnalog(uint8_t pin, int value)
{
  // pin can only be 0-15, so chop higher bits
  putch(ANALOG_MESSAGE | (pin & 0xF));
  sendValueAsTwo7bitBytes(value);
}

// send a single digital pin in a digital message
void Firmata_sendDigital(uint8_t pin, int value)
{
  /* TODO add single pin digital messages to the protocol, this needs to
   * track the last digital data sent so that it can be sure to change just
   * one bit in the packet.  This is complicated by the fact that the
   * numbering of the pins will probably differ on Arduino, Wiring, and
   * other boards.
   */

  // TODO: the digital message should not be sent on the serial port every
  // time sendDigital() is called.  Instead, it should add it to an int
  // which will be sent on a schedule.  If a pin changes more than once
  // before the digital message is sent on the serial port, it should send a
  // digital message for each change.

  //    if(value == 0)
  //        sendDigitalPortPair();
}


// send 14-bits in a single digital message (protocol v1)
// send an 8-bit port in a single digital message (protocol v2)
void Firmata_sendDigitalPort(uint8_t portNumber, int portData)
{
  putch(DIGITAL_MESSAGE | (portNumber & 0xF));
  putch((uint8_t)portData % 128); // Tx bits 0-6
  putch(portData >> 7);  // Tx bits 7-13
}

void sendSysex(uint8_t command, uint8_t bytec, uint8_t *bytev)
{
  uint8_t i;
  startSysex();
  putch(command);
  for (i = 0; i < bytec; i++) {
    sendValueAsTwo7bitBytes(bytev[i]);
  }
  endSysex();
}

void sendCmdString(uint8_t command, const char *string)
{
  sendSysex(command, strlen(string), (uint8_t *)string);
}

// send a string as the protocol string type
void sendString(const char *string)
{
  sendCmdString(STRING_DATA, string);
}

// expose the write method
void Firmata_write(uint8_t c)
{
  putch(c);
}

// Internal Actions/////////////////////////////////////////////////////////////

// generic callbacks
//void Firmata_attach(uint8_t command, void* newFunction)
//{
//  switch (command) {
//    case ANALOG_MESSAGE: currentAnalogCallback = newFunction; break;
//    case DIGITAL_MESSAGE: currentDigitalCallback = newFunction; break;
//    case REPORT_ANALOG: currentReportAnalogCallback = newFunction; break;
//    case REPORT_DIGITAL: currentReportDigitalCallback = newFunction; break;
//    case SET_PIN_MODE: currentPinModeCallback = newFunction; break;
//    case SET_DIGITAL_PIN_VALUE: currentPinValueCallback = newFunction; break;
//    case SYSTEM_RESET: currentSystemResetCallback = newFunction; break;
//    case STRING_DATA: currentStringCallback = newFunction; break;
//      default:  currentSysexCallback = newFunction;
//  }
//}
//
//void detach(uint8_t command)
//{
//  switch (command) {
//    case SYSTEM_RESET: currentSystemResetCallback = NULL; break;
//    case STRING_DATA: currentStringCallback = NULL; break;
//    case START_SYSEX: currentSysexCallback = NULL; break;
//    default:
//      Firmata_attach(command, (callbackFunction)NULL);
//  }
//}

// sysex callbacks
/*
 * this is too complicated for analogReceive, but maybe for Sysex?
 void attachSysex(sysexFunction newFunction)
 {
 uint8_t i;
 uint8_t tmpCount = analogReceiveFunctionCount;
 analogReceiveFunction* tmpArray = analogReceiveFunctionArray;
 analogReceiveFunctionCount++;
 analogReceiveFunctionArray = (analogReceiveFunction*) calloc(analogReceiveFunctionCount, sizeof(analogReceiveFunction));
 for(i = 0; i < tmpCount; i++) {
 analogReceiveFunctionArray[i] = tmpArray[i];
 }
 analogReceiveFunctionArray[tmpCount] = newFunction;
 free(tmpArray);
 }
*/

//******************************************************************************
//* Private Methods
//******************************************************************************

// resets the system state upon a SYSTEM_RESET message from the host software
void systemReset(void)
{
  uint8_t i;

  waitForData = 0; // this flag says the next serial input will be data
  mbCmd = 0; // execute this after getting multi-uint8_t data
  mbChn = 0; // channel data for multiByteCommands

  for (i = 0; i < MAX_DATA_BYTES; i++) {
    inBuf[i] = 0;
  }

  parsingSysex = false;
  sysexBytesRead = 0;

//  if (currentSystemResetCallback)
//    (*currentSystemResetCallback)();
}

// =============================================================================
// used for flashing the pin for the version number
void strobeBlinkPin(uint8_t pin, int count)
{
  uint8_t i;
  for (i = 0; i < count; i++) {
    delay(210);
    digitalWrite(pin, HIGH);
    delay(40);
    digitalWrite(pin, LOW);
  }
}
