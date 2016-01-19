/* 
 * File:   xpress.h
 * Author: Lucio Di Jasio
 *
 * Created on 15 January 2016
 */

#ifndef XPRESS_H
#define	XPRESS_H

#include "mcc_generated_files/mcc.h"

#define XPRESS_18855        // identify board type

#define delay(x)    __delay_ms(x)

#define Serial_DataReady()  EUSART_DataReady

#define NUM_DIGITAL_PINS    22
#define NUM_ANALOG_PINS     22
#define TOTAL_NUM_PINS      24

typedef enum {  A0=0, A1, A2, A3, A4, A5, A6, A7, 
        B0, B1, B2, B3, B4, B5, B6, B7, 
        C0, C1, C2, C3, C4, C5, C6, C7, NC } pin_t;

// pin modes
#define PIN_MODE_INPUT          0x00 // digital input
#define PIN_MODE_OUTPUT         0x01 // digital output
#define PIN_MODE_ANALOG         0x02 // analog pin in analogInput mode
#define PIN_MODE_PWM            0x03 // digital pin in PWM output mode
#define PIN_MODE_SERVO          0x04 // digital pin in Servo output mode
#define PIN_MODE_SHIFT          0x05 // shiftIn/shiftOut mode
#define PIN_MODE_I2C            0x06 // pin included in I2C setup
#define PIN_MODE_ONEWIRE        0x07 // pin configured for 1-wire
#define PIN_MODE_STEPPER        0x08 // pin configured for stepper motor
#define PIN_MODE_ENCODER        0x09 // pin configured for rotary encoders
#define PIN_MODE_SERIAL         0x0A // pin configured for serial communication
#define PIN_MODE_PULLUP         0x0B // enable internal pull-up resistor for pin
#define PIN_MODE_IGNORE         0x7F // pin configured to be ignored by digitalWrite and capabilityResponse
        
#define SS      B2
#define CS      B2
#define SCK     B3
#define MISO    B4
#define MOSI    B5
#define SDA     C3
#define SCL     C4
#define POT     A4
#define SW      A5        
#define INT     C2
#define PWM     C7
#define AN      B0
#define RST     B1
        
#define LED_BUILTIN     LED0
#define LED0            A0
#define LED1            A1
#define LED2            A2
#define LED3            A3

uint8_t digitalRead( pin_t pin);
void digitalWrite(pin_t pin, uint8_t value);
void pinMode(pin_t pin, uint8_t mode);
uint8_t getMode( pin_t pin);
uint16_t analogRead(pin_t pin);

uint8_t readPort(uint8_t port);
void writePort(uint8_t port, uint8_t value);

#define servoWrite(p, v) pwmWrite(p, v)
#define analogWrite(p, v) pwmWrite(p, v)
void pwmWrite(pin_t pin, uint16_t value);


#endif	/* XPRESS_H */

