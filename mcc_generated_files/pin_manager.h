/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v3.0 Beta
        Device            :  PIC16F18855
        Version           :  1.01
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


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SS1 aliases
#define SS1_TRIS               TRISA5
#define SS1_LAT                LATA5
#define SS1_PORT               RA5
#define SS1_WPU                WPUA5
#define SS1_ANS                ANSA5
#define SS1_SetHigh()    do { LATA5 = 1; } while(0)
#define SS1_SetLow()   do { LATA5 = 0; } while(0)
#define SS1_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define SS1_GetValue()         RA5
#define SS1_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define SS1_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define SS1_SetPullup()    do { WPUA5 = 1; } while(0)
#define SS1_ResetPullup()   do { WPUA5 = 0; } while(0)
#define SS1_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define SS1_SetDigitalMode()   do { ANSA5 = 0; } while(0)


// get/set SS1 aliases
#define SS1_TRIS               TRISA5
#define SS1_LAT                LATA5
#define SS1_PORT               RA5
#define SS1_WPU                WPUA5
#define SS1_ANS                ANSA5
#define SS1_SetHigh()    do { LATA5 = 1; } while(0)
#define SS1_SetLow()   do { LATA5 = 0; } while(0)
#define SS1_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define SS1_GetValue()         RA5
#define SS1_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define SS1_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define SS1_SetPullup()    do { WPUA5 = 1; } while(0)
#define SS1_ResetPullup()   do { WPUA5 = 0; } while(0)
#define SS1_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define SS1_SetDigitalMode()   do { ANSA5 = 0; } while(0)


// get/set RST aliases
#define RST_TRIS               TRISB1
#define RST_LAT                LATB1
#define RST_PORT               RB1
#define RST_WPU                WPUB1
#define RST_ANS                ANSB1
#define RST_SetHigh()    do { LATB1 = 1; } while(0)
#define RST_SetLow()   do { LATB1 = 0; } while(0)
#define RST_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define RST_GetValue()         RB1
#define RST_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define RST_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define RST_SetPullup()    do { WPUB1 = 1; } while(0)
#define RST_ResetPullup()   do { WPUB1 = 0; } while(0)
#define RST_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define RST_SetDigitalMode()   do { ANSB1 = 0; } while(0)


// get/set CS aliases
#define CS_TRIS               TRISB2
#define CS_LAT                LATB2
#define CS_PORT               RB2
#define CS_WPU                WPUB2
#define CS_ANS                ANSB2
#define CS_SetHigh()    do { LATB2 = 1; } while(0)
#define CS_SetLow()   do { LATB2 = 0; } while(0)
#define CS_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define CS_GetValue()         RB2
#define CS_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define CS_SetPullup()    do { WPUB2 = 1; } while(0)
#define CS_ResetPullup()   do { WPUB2 = 0; } while(0)
#define CS_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define CS_SetDigitalMode()   do { ANSB2 = 0; } while(0)


// get/set CS aliases
#define CS_TRIS               TRISB2
#define CS_LAT                LATB2
#define CS_PORT               RB2
#define CS_WPU                WPUB2
#define CS_ANS                ANSB2
#define CS_SetHigh()    do { LATB2 = 1; } while(0)
#define CS_SetLow()   do { LATB2 = 0; } while(0)
#define CS_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define CS_GetValue()         RB2
#define CS_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define CS_SetPullup()    do { WPUB2 = 1; } while(0)
#define CS_ResetPullup()   do { WPUB2 = 0; } while(0)
#define CS_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define CS_SetDigitalMode()   do { ANSB2 = 0; } while(0)


// get/set CS aliases
#define CS_TRIS               TRISB2
#define CS_LAT                LATB2
#define CS_PORT               RB2
#define CS_WPU                WPUB2
#define CS_ANS                ANSB2
#define CS_SetHigh()    do { LATB2 = 1; } while(0)
#define CS_SetLow()   do { LATB2 = 0; } while(0)
#define CS_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define CS_GetValue()         RB2
#define CS_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define CS_SetPullup()    do { WPUB2 = 1; } while(0)
#define CS_ResetPullup()   do { WPUB2 = 0; } while(0)
#define CS_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define CS_SetDigitalMode()   do { ANSB2 = 0; } while(0)


// get/set CS aliases
#define CS_TRIS               TRISB2
#define CS_LAT                LATB2
#define CS_PORT               RB2
#define CS_WPU                WPUB2
#define CS_ANS                ANSB2
#define CS_SetHigh()    do { LATB2 = 1; } while(0)
#define CS_SetLow()   do { LATB2 = 0; } while(0)
#define CS_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define CS_GetValue()         RB2
#define CS_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define CS_SetPullup()    do { WPUB2 = 1; } while(0)
#define CS_ResetPullup()   do { WPUB2 = 0; } while(0)
#define CS_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define CS_SetDigitalMode()   do { ANSB2 = 0; } while(0)


// get/set CS aliases
#define CS_TRIS               TRISB2
#define CS_LAT                LATB2
#define CS_PORT               RB2
#define CS_WPU                WPUB2
#define CS_ANS                ANSB2
#define CS_SetHigh()    do { LATB2 = 1; } while(0)
#define CS_SetLow()   do { LATB2 = 0; } while(0)
#define CS_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define CS_GetValue()         RB2
#define CS_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define CS_SetPullup()    do { WPUB2 = 1; } while(0)
#define CS_ResetPullup()   do { WPUB2 = 0; } while(0)
#define CS_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define CS_SetDigitalMode()   do { ANSB2 = 0; } while(0)


// get/set CS aliases
#define CS_TRIS               TRISB2
#define CS_LAT                LATB2
#define CS_PORT               RB2
#define CS_WPU                WPUB2
#define CS_ANS                ANSB2
#define CS_SetHigh()    do { LATB2 = 1; } while(0)
#define CS_SetLow()   do { LATB2 = 0; } while(0)
#define CS_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define CS_GetValue()         RB2
#define CS_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define CS_SetPullup()    do { WPUB2 = 1; } while(0)
#define CS_ResetPullup()   do { WPUB2 = 0; } while(0)
#define CS_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define CS_SetDigitalMode()   do { ANSB2 = 0; } while(0)


// get/set INT aliases
#define INT_TRIS               TRISC2
#define INT_LAT                LATC2
#define INT_PORT               RC2
#define INT_WPU                WPUC2
#define INT_ANS                ANSC2
#define INT_SetHigh()    do { LATC2 = 1; } while(0)
#define INT_SetLow()   do { LATC2 = 0; } while(0)
#define INT_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define INT_GetValue()         RC2
#define INT_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define INT_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define INT_SetPullup()    do { WPUC2 = 1; } while(0)
#define INT_ResetPullup()   do { WPUC2 = 0; } while(0)
#define INT_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define INT_SetDigitalMode()   do { ANSC2 = 0; } while(0)


// get/set INT aliases
#define INT_TRIS               TRISC2
#define INT_LAT                LATC2
#define INT_PORT               RC2
#define INT_WPU                WPUC2
#define INT_ANS                ANSC2
#define INT_SetHigh()    do { LATC2 = 1; } while(0)
#define INT_SetLow()   do { LATC2 = 0; } while(0)
#define INT_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define INT_GetValue()         RC2
#define INT_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define INT_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define INT_SetPullup()    do { WPUC2 = 1; } while(0)
#define INT_ResetPullup()   do { WPUC2 = 0; } while(0)
#define INT_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define INT_SetDigitalMode()   do { ANSC2 = 0; } while(0)


// get/set INT aliases
#define INT_TRIS               TRISC2
#define INT_LAT                LATC2
#define INT_PORT               RC2
#define INT_WPU                WPUC2
#define INT_ANS                ANSC2
#define INT_SetHigh()    do { LATC2 = 1; } while(0)
#define INT_SetLow()   do { LATC2 = 0; } while(0)
#define INT_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define INT_GetValue()         RC2
#define INT_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define INT_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define INT_SetPullup()    do { WPUC2 = 1; } while(0)
#define INT_ResetPullup()   do { WPUC2 = 0; } while(0)
#define INT_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define INT_SetDigitalMode()   do { ANSC2 = 0; } while(0)


// get/set RX aliases
#define RX_TRIS               TRISC7
#define RX_LAT                LATC7
#define RX_PORT               RC7
#define RX_WPU                WPUC7
#define RX_ANS                ANSC7
#define RX_SetHigh()    do { LATC7 = 1; } while(0)
#define RX_SetLow()   do { LATC7 = 0; } while(0)
#define RX_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define RX_GetValue()         RC7
#define RX_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define RX_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define RX_SetPullup()    do { WPUC7 = 1; } while(0)
#define RX_ResetPullup()   do { WPUC7 = 0; } while(0)
#define RX_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define RX_SetDigitalMode()   do { ANSC7 = 0; } while(0)



/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
*/