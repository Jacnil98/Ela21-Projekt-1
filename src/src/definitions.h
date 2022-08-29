#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

//Sätter klockfrekvensen till 16 MHz. 

/******************************************************************************
* Inkluderingsdirektiv:
*******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/******************************************************************************
* Makron för hantering av avbrott.
******************************************************************************/
#define ENABLE_INTERRUPTS asm("SEI")    
#define DISABLE_INTERRUPTS asm("CLI")
 
#define CLEAR(REGISTER) REGISTER = 0x00
// Typdefinitioner:
typedef enum { false, true } bool;

#endif /* DEFINTIONS_H_ */
