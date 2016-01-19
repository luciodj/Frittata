/**
  CCP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp1.c

  @Summary
    This is the generated driver implementation file for the CCP1 driver using MPLAB� Code Configurator

  @Description
    This source file provides implementations for driver APIs for CCP1.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.25.2
        Device            :  PIC16F1619
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
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

/**
  Section: Included Files
 */

#include <xc.h>
#include "pwm5.h"

/**
  Section: Macro Declarations
 */


/**
  Section: PWM Module APIs
 */

void PWM5_Initialize(void) {
    // Set the PWM to the options selected in the MPLAB� Code Configurator

    // MODE PWM; EN enabled; FMT right_aligned; 
    CCP5CON = 0x8F;

    // RH 0; 
    CCPR5H = 0x00;

    // RL 0; 
    CCPR5L = 0x00;

    // Selecting Timer2
    CCPTMRS1bits.C5TSEL = 0x1;
}

void PWM5_DutyValueSet(uint16_t dutyValue) {
    dutyValue &= 0x03FF;

    // Load duty cycle value
    if (CCP5CONbits.FMT) {
        dutyValue <<= 6;
        CCPR5H = dutyValue >> 8;
        CCPR5L = dutyValue;
    } else {
        CCPR5H = dutyValue >> 8;
        CCPR5L = dutyValue;
    }
}

bool PWM5_OutputStatusGet(void) {
    // Returns the output status
    return (CCP5CONbits.OUT);
}
/**
 End of File
 */

