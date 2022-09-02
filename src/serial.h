#ifndef SERIAL_H_
#define SERIAL_H_

/* Include directive */
#include "definitions.h"

/* Sets the maximum value of a string */
#define SIZE 50

/**
 * @brief type definition of the struct Serial
 * @details no variable members present, but has
 * function pointers. To print a number using
 * one of the functions requires the string to contain
 * a format specifier, like "%d".
 */
typedef struct Serial
{
	void (*print)(const char*);
	void (*print_unsigned)(const char*, const uint32_t);
	void (*print_signed)(const char*, const int32_t);
	void (*print_decimal)(const char*, const double);
} Serial;

/* External functions */
Serial new_Serial();

#endif /* SERIAL_H_ */