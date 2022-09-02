#ifndef _HEADER_H_
#define _HEADER_H_

#include "definitions.h"
#include "serial.h"
#include "lin_reg.h"
#include "timer.h"
#include "Array.h"

#define BUTTON 5 // PIN 13 / PORTB5.
#define TEMP_SENSOR 1 // PIN A1 / PORTC1.

// Makron för beräkning av temperatur:
#define Vcc 5.0f
#define ADC_MAX 1023

lin_reg l1;
Serial serial;
Timer timer0, timer1, timer2;
Array arr;

void setup();
void print_temp();
double ADC_return();

#endif /* HEADER_H_ */