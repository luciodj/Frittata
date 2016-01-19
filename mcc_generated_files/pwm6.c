/**
  PWM6 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm6.c

  @Summary
    This is the generated driver implementation file for the PWM4 driver using MPLAB� Code Configurator

  @Description
    This source file provides implementations for driver APIs for PWM4.
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
#include "pwm6.h"

/**
  Section: PWM Module APIs
 */

void PWM6_Initialize(void) {
    // Set the PWM to the options selected in the MPLAB� Code Configurator.
    // PWMxPOL active_hi; PWMxEN enabled; 
    PWM6CON = 0x80;

    // PWMxDCH 0; 
    PWM6DCH = 0;

    // PWMxDCL 0 
    PWM6DCL = 0;


    // Select timer
    CCPTMRS1bits.P6TSEL = 0x0;
}

void PWM6_DutyValueSet(uint16_t dutyValue) {
    // Writing to 8 MSBs of PWM duty cycle in PWMDCH register
    PWM6DCH = (dutyValue & 0x03FC) >> 2;

    // Writing to 2 LSBs of PWM duty cycle in PWMDCL register
    PWM6DCL = (dutyValue & 0x0003) << 6;
}
/**
 End of File
 */