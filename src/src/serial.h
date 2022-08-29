
#ifndef SERIAL_H_
#define SERIAL_H_

// Inkluderingsdirektiv:
#include "definitions.h"
#include <stdio.h>

// Makron för strängstorlekar:
#define SIZE 50 // Ordinarie strängstorlek.

typedef struct Serial
{
	void (*print)(const char*);
	void (*println)(const char*);
	void (*print_unsigned)(const char*, const uint32_t);
	void (*print_signed)(const char*, const int32_t);
} Serial;

Serial new_Serial();

#endif /* SERIAL_H_ */