/*
 * File: Xpress.c
 * 
 * Author: Lucio Di Jasio
 * 
 * A PORT and Pin control API inspired by Wiring for the PIC16F188xx
 * Default pin assignemnts are based on the MPLAB Xpress board.
 * 
 */
#include "Xpress.h"
#include "Frittata.h"

uint8_t _pin_mode[] = { 
    PIN_MODE_OUTPUT,PIN_MODE_OUTPUT,PIN_MODE_OUTPUT,PIN_MODE_OUTPUT,// LED0..3
    PIN_MODE_ANALOG,PIN_MODE_INPUT,PIN_MODE_INPUT,PIN_MODE_INPUT,   // POT, SW, ALRM1, ALRM2
    PIN_MODE_ANALOG,PIN_MODE_OUTPUT,PIN_MODE_OUTPUT,PIN_MODE_OUTPUT,// AN, RST, CS, SCK
    PIN_MODE_INPUT,PIN_MODE_OUTPUT,PIN_MODE_IGNORE,PIN_MODE_IGNORE, // MISO, MOSI, NC, NC
    PIN_MODE_SERIAL,PIN_MODE_SERIAL,PIN_MODE_INPUT,PIN_MODE_I2C,    // TX-USB, RX-USB, INT, SDA 
    PIN_MODE_I2C,PIN_MODE_SERIAL,PIN_MODE_SERIAL,PIN_MODE_PWM       // SCL, TX, RX, PWM
}; 

uint8_t readPort( uint8_t port)
{
    switch(port) {
        case 0: return PORTA;
        case 1: return PORTB;               
        case 2: return PORTC;
    }
    return 0;
}

uint8_t digitalRead( pin_t pin)
{
    switch(pin >> 3) {
        case 0: // PORTA
            return (PORTA >> (pin & 7)) & 1;
        case 1: // PORTB
            return (PORTB >> (pin & 7)) & 1;
        case 2: // PORTC
            return (PORTC >> (pin & 7)) & 1;
        default:
            return 0;
    }
}

uint16_t analogRead( pin_t pin)
{
    return (uint16_t) ADCC_GetSingleConversion( pin);
}

void writePort(uint8_t port, uint8_t mask)
{
    switch(port) {
    case 0:  LATA = mask; break;
    case 1:  LATB = mask; break;
    case 2:  LATC = mask; break;
    }
}

void digitalWrite(pin_t pin, uint8_t value)
{
    uint8_t mask = 1 << (pin & 7);
    switch(pin >> 3) {
      case 0:   LATA = (LATA & ~mask) | ((value & 1) << (pin & 7)); break;
      case 1:   LATB = (LATB & ~mask) | ((value & 1) << (pin & 7)); break;
      case 2:   LATC = (LATC & ~mask) | ((value & 1) << (pin & 7)); break;
    }
}

// --------------------------------------------------------------------
// PWM pin management

void _pwmDutyValue( uint8_t chn, uint16_t value)
{
    switch(chn) {
        case 0: PWM1_DutyValueSet( value); break;
        case 1: PWM2_DutyValueSet( value); break;
        case 2: PWM3_DutyValueSet( value); break;
        case 3: PWM4_DutyValueSet( value); break;
        case 4: PWM5_DutyValueSet( value); break;
        case 5: PWM6_DutyValueSet( value); break;
        case 6: PWM7_DutyValueSet( value); break;
        default: break;
    }
}

#define PPS_FUN_CCP1     0x09       // PPS function for CCP1 output

void _ppsOutputFunction(pin_t pin, uint8_t f)
{
    uint8_t *pps_ptr = (void*)&RA0PPS;
    if (pin < sizeof(_pin_mode)) 
        pps_ptr[pin] = f;
}

pin_t _pwm_in_use[] = { NC, NC, NC, NC, NC, NC, NC};   // PWM1..7 available


/**
 * check if pin is in pwm/servo mode (analog output) 
 * 
 * @return currently assigned pwm channel (-1 if not)
 */
uint8_t _getPwmChannel(pin_t pin)
{
    uint8_t i;
    for(i=0; i< sizeof(_pwm_in_use); i++)
        if (_pwm_in_use[i] == pin)         
            return i;
    return 0xff;
}

uint8_t _assignPwmChannel(pin_t pin)
{
    uint8_t chn, last;
    switch(pin >> 3){
        case 0: chn = 4; last = 6; break; // PORTA can only take chn 5, 6, 7
        case 1: chn = 0; last = 3; break; // PORTB can only take chn 0, 1, 2, 3
        case 2: chn = 0; last = 6; break; // PORTC can only take all channels
    }
    for(; chn<=last; chn++)
        if (_pwm_in_use[chn] == NC) {
            _pwm_in_use[chn] = pin; // assign to pin
            _pwmDutyValue(chn, 0);  // init pwm dutycycle value
            _ppsOutputFunction(pin, PPS_FUN_CCP1+chn);      // connect pin via PPS
            return chn;
        }
    return 0xff;    
}

void _freePwmChannel(pin_t pin)
{
    //check if a pwm channel was assigned
    uint8_t chn = _getPwmChannel( pin);
    if ( chn < sizeof(_pwm_in_use)) {        
        _pwm_in_use[chn] = NC;  // disconnect the channel
        _ppsOutputFunction(pin, 0);   // return pin to I/O control
    }
}

void pwmWrite(pin_t pin, uint16_t value)
{
    uint8_t chn;
    chn = _getPwmChannel(pin);
    if (chn < sizeof(_pwm_in_use))
        _pwmDutyValue( chn, value);
}


void pinMode(pin_t pin, uint8_t mode)
{
    uint8_t mask = 1 << (pin & 7);
    uint8_t port = pin >> 3;
    if (mode != PIN_MODE_PULLUP)
        _pin_mode[pin] = mode;
    switch(mode){
        case PIN_MODE_INPUT:    // make pure digital input
            switch(port){
                case 0: TRISA |= mask; ANSELA &= ~mask; break;
                case 1: TRISB |= mask; ANSELB &= ~mask; break;
                case 2: TRISC |= mask; ANSELC &= ~mask; break;
                default: break;
            }
            break;
        case PIN_MODE_OUTPUT:   // enable digital output (analog input possible)
            switch(port){
                case 0: TRISA &= ~mask; break;
                case 1: TRISB &= ~mask; break;
                case 2: TRISC &= ~mask; break;
                default: break;
            }
            break;
        case PIN_MODE_ANALOG:   // make pure analog input
            switch(port){
                case 0: ANSELA |= mask; TRISA |= mask; break;
                case 1: ANSELB |= mask; TRISB |= mask; break;
                case 2: ANSELC |= mask; TRISC |= mask; break;
                default: break;
            }
            break;
        case PIN_MODE_PWM:
        case PIN_MODE_SERVO: 
            { //    check if pin has already a PWM assigned
                uint8_t chn = _getPwmChannel(pin);
                //    check if a new PWM is available
                if (chn > sizeof(_pwm_in_use)) {
                    chn = _assignPwmChannel( pin);
                }                
            }
            break;
        case PIN_MODE_PULLUP:   // enable pullups, does not affect other settings
            switch(port){
                case 0: WPUA |= mask; break;
                case 1: WPUB |= mask; break;
                case 2: WPUC |= mask; break;
                default: break;
            }
            break;
        default:
            break;
    }
}

uint8_t getMode( pin_t pin)
{
    if ( pin < sizeof(_pin_mode))
        return _pin_mode[ pin]; 
    else 
        return PIN_MODE_IGNORE;
}


