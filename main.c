/**
 Standard Frittata

 Author:
    Lucio Di Jasio.

  File Name:
    main.c

  Summary:
    Implements callbacks and main loop for a stabdard Frittata setup.
    
  Description:
      Frittata is based on the popular Firmata library. The standard setup 
        demonstrates the use of the library to allow remote access via PC to all
        i/o analog and digital board functions.
  
  The generated drivers are tested against the following:
        Compiler          :  XC8 v1.35
        MPLAB             :  MPLAB X v3.20
*/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#include "mcc_generated_files/mcc.h"
#include "Frittata.h"

uint32_t analogReps = 0;
uint8_t portReps[3];
uint8_t prevPort[3];

void Callback( uint8_t cmd, uint8_t par, int value)
{
    switch (cmd) {
      case ANALOG_MESSAGE:
        analogWrite(par, value);    // pin, duty
        break;
      case DIGITAL_MESSAGE:
          writePort(par, value);    // port, mask
        break;
      case SET_PIN_MODE:
          pinMode(par, value);      // pin, mode
        break;
      case SET_DIGITAL_PIN_VALUE:
        break;
      case REPORT_ANALOG:
          if (value) analogReps = analogReps | (1 << par);
          else       analogReps = analogReps & ~(1 << par);          
        break;
      case REPORT_DIGITAL:
          portReps[par] = (uint8_t) value; // port, mask
          LATA = value;
        break;
  }
}

void checkDigitalInputs(void)
{
    uint8_t port, value;
    for(port=0; port<sizeof(portReps); port++){
        if (portReps[port]) {
            value = readPort(port) & portReps[port];    // check only pins requested
            if (prevPort[port] != value) {
                Firmata_sendDigitalPort(port, value);
                prevPort[port] = value;
            }
        }
    }
}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    Firmata_initialize();
    Firmata_begin();
    
    while (1)
    {
        while (Firmata_available()) {
            Firmata_processInput();
        }
        
        checkDigitalInputs();
        
//        if (getMode(pin) == PIN_MODE_ANALOG)
//            Firmata_sendAnalog(pin, analogRead(pin));
//        pin++;
//        if (pin == TOTAL_NUM_PINS) pin = 0;
    }
}
/**
 End of File
*/