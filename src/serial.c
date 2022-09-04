/* Include directives */

#include "Serial.h"

/* Static functions */

static void Serial_print(const char *s);
static void Serial_print_unsigned(const char *s, const uint32_t number);
static void Serial_print_signed(const char *s, const int32_t number);
static void Serial_print_decimal(const char *s, const double number);
static void init_serial();
static void write_byte(const char data);

/**
 * @brief sets function pointers to point at local functions and
 * initiates serial transmission for the arduino uno.
 * 
 * @return initiated instance of struct Serial 
 */
Serial new_Serial()
{
	Serial self;
	self.print = Serial_print;
	self.print_unsigned = Serial_print_unsigned;
	self.print_signed = Serial_print_signed;
	self.print_decimal = Serial_print_decimal;
	init_serial();
	return self;
}

/**
 * @brief prints out a string through serial communication
 * 
 * @param s String of text to print out.
 */
static void Serial_print(const char *s)
{
	for (uint16_t i = 0; s[i] != '\0'; i++)
	{
		write_byte(s[i]);
		if (s[i] == '\n')
			write_byte('\r');
	}

	/* write_byte('\0'); not used since it prints NUL in VS code terminal */
	return;
}

/**
 * @brief prints a unsigned integer by combining a string and number by
 * using sprintf and then sending that string function Serial_print
 *
 * @param s String of text that has a format specifier %d
 * @param number a unsigned integer.
 */
static void Serial_print_unsigned(const char *s, const uint32_t number)
{
	char text[SIZE];
	text[0] = '\0';
	sprintf(text, s, number);
	Serial_print(text);
	return;
}

/**
 * @brief prints a signed integer by combining a string and number by
 * using sprintf and then sending that string function Serial_print
 *
 * @param s String of text that has a format specifier %d
 * @param number a signed integer.
 */
static void Serial_print_signed(const char *s, const int32_t number)
{
	char text[SIZE];
	text[0] = '\0';
	sprintf(text, s, number);
	Serial_print(text);
	return;
}

/**
 * @brief print_decimal uses sprintf to combine a decimal number which
 * is split up by using modulo operator and then put together by passing
 * a string with the format "%d.%d%d"
 * @example Serial_print_decimal("Decimal number: %d.%d%d", 3.52)
 * prints out: Decimal number: 3.52
 *
 * @param s String of text, to get two decimals use "%d.%d%d"
 * @param number double, a 2 point decimal number to be printed.
 */
static void Serial_print_decimal(const char *s, const double number)
{
	const int integer = (int)number;			 // 3.52 blir 3, -3.52 blir -3.
	int first_decimal = (int)(number * 10) % 10; // (3.52 - 3) * 100 = 52.
	int second_decimal = (int)(number * 100) % 10;
	char text[SIZE];
	text[0] = '\0';

	if (first_decimal < 0)
	{
		first_decimal *= -1; // Om det blev -52, sätter vi det till 52 => utskriften blir -3.52.
	}
	if (second_decimal < 0)
	{
		second_decimal *= -1;
	}

	sprintf(text, s, integer, first_decimal, second_decimal);
	Serial_print(text);
	return;
}

/**
 * @brief initiates serial transmission.
 * sets the size of the transmission and the
 * baudrate to 9600.
 */
static void init_serial()
{
	UCSR0B = (1 << TXEN0);
	UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01));
	UBRR0 = 103;
	write_byte('\r');
	return;
}

/**
 * @brief sends one byte of data through
 * serial transmission, one byte at a time.
 * 
 * @param data byte to be transmitted.
 */
static void write_byte(const char data)
{
	while ((UCSR0A & (1 << UDRE0)) == 0)
		;
	UDR0 = data;
	return;
}