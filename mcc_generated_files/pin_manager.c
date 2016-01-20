/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v3.0 Beta
        Device            :  PIC16F18855
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.35
        MPLAB             :  MPLAB X v3.10

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

#include <xc.h>
#include "pin_manager.h"
#include <stdbool.h>

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x0;
    LATB = 0x4;
    LATC = 0x0;
    WPUE = 0x8;
    WPUA = 0;
    WPUB = 0;
    WPUC = 0;
    ANSELA = 0x10;
    ANSELB = 0;
    ANSELC = 0;
    TRISA = 0xF0;
    TRISB = 0x11;
    TRISC = 0x9E;

    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    T2AINPPSbits.T2AINPPS = 0x0013;   //RC3->TMR2:T2IN;
    RC0PPS = 0x0010;   //RC0->EUSART:TX;
    SSP1DATPPSbits.SSP1DATPPS = 0x000C;   //RB4->MSSP1:SDI1;
    RXPPSbits.RXPPS = 0x0011;   //RC1->EUSART:RX;
    ADCACTPPS = 0x000C;   //RB4->ADC:ADCACT;
    RB5PPS = 0x0015;   //RB5->MSSP1:SDO1;
    RB3PPS = 0x0014;   //RB3->MSSP1:SCK1;
    SSP2DATPPSbits.SSP2DATPPS = 0x0013;   //RC3->MSSP2:SDA2;
    SSP2CLKPPSbits.SSP2CLKPPS = 0x0014;   //RC4->MSSP2:SCL2;

//    PPSLOCK = 0x55;
//    PPSLOCK = 0xAA;
//    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;
}
/**
 End of File
*/