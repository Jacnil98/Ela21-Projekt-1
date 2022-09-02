#ifndef _HEADER_H_
#define _HEADER_H_

/* Include directives */
#include "definitions.h"
#include "serial.h"
#include "lin_reg.h"
#include "timer.h"
#include "Array.h"

/* Defines button pin */
#define BUTTON 5 

/* Defines temperature sensor pin */
#define TEMP_SENSOR 1 

/* Macro for AD-conversion */
#define Vcc 5.0f
#define ADC_MAX 1023

/* Global linear regression variables */
lin_reg l1;

/* Global serial variable */
Serial serial;

/**
 * @brief Struct object of Timer
 * 	@param timer0 Debounce timer for button
 *	@param timer1 Counter for adjusting timer2
 *	@param timer2 Adaptive timer for printing temp.
 */
Timer timer0, timer1, timer2;

Array arr;

/* External functions */
void setup();
void print_temp();
double ADC_return();

#endif /* HEADER_H_ */