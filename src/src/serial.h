#ifndef SERIAL_H_
#define SERIAL_H_

/* Includefiles */
#include "definitions.h"

/* Sets the maximum value of a string */
#define SIZE 50

/**
 * @brief type definition of the struct Serial
 */
typedef struct Serial
{
	void (*print)(const char*);
	void (*println)(const char*);
	void (*print_unsigned)(const char*, const uint32_t);
	void (*print_signed)(const char*, const int32_t);
	void (*print_decimal)(const char*, const double);
} Serial;

/* External functions */
Serial new_Serial();

#endif /* SERIAL_H_ */