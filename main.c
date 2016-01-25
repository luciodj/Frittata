/**
 Project:  Standard Frittata

 Author:
    Lucio Di Jasio.

  File Name:
    main.c

  Summary:
    Implements callbacks and main loop for a Standard Frittata setup.
    
  Description:
    Frittata is based on the popular Firmata library ( http://firmata.org). 
    The standard setup demonstrates the use of the library to allow remote 
    access from a PC to all i/o analog and digital functions of the MPLAB Xpress
    board.
  
  The generated drivers are tested against the following:
        Compiler          :  XC8 v1.35
        MPLAB             :  MPLAB X v3.20
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
      case REPORT_ANALOG:           // pin, enable/disable
          if (value) analogReps = analogReps | (1 << par);
          else       analogReps = analogReps & ~(1 << par);          
        break;
      case REPORT_DIGITAL:
          portReps[par] = (uint8_t) value; // port, 1/0 enable/disable
          Firmata_sendDigitalPort(par, readPort(par)); // send first snapshot
        break;
  }
}

void checkDigitalInputs(void)
{
    uint8_t port, value;
    for(port=0; port<sizeof(portReps); port++){
        if (portReps[port]) {
            value = readPort(port) ;    // check entire ports enabled 
            if (prevPort[port] != value) {
                Firmata_sendDigitalPort(port, value);
                prevPort[port] = value;
            }
        }
    }
}

void reportAnalogInputs(void)
{
    static uint8_t pin=0;
    if (analogReps >> pin) 
        Firmata_sendAnalog(pin, analogRead(pin));
    pin++;
    if (pin > NUM_ANALOG_PINS) 
        pin = 0;
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
        reportAnalogInputs();
        
    }
}
/**
 End of File
*/