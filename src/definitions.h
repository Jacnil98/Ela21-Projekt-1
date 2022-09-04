#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/* Include directives */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* asm interrupt macro */

#define ENABLE_INTERRUPTS asm("SEI")    
#define DISABLE_INTERRUPTS asm("CLI")
 
/* Bool enumeration */
typedef enum { false, true } bool;

#endif /* DEFINTIONS_H_ */
