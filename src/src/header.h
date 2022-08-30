#ifndef _HEADER_H_
#define _HEADER_H_

#include "definitions.h"
#include "serial.h"
#include "lin_reg.h"
#include "timer.h"

#define BUTTON 5 // PIN 13 / PORTB5.

#define TEMP_SENSOR 1 // PIN A1 / PORTC1.

// Makron för beräkning av temperatur:
#define Vcc 5.0f // Matningsspänning 5 V.
#define ADC_MAX 1023 // Maxvärde vid AD-omvandling.
struct lin_reg l1;
Serial serial;
Timer timer1, timer2;
volatile uint8_t executed_interrupts;

void setup();
void print_temp();
double ADC_return();

#endif /* HEADER_H_ */