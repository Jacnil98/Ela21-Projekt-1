#include "Serial.h"

static void Serial_print(const char* s);
static void Serial_println(const char* s);
static void Serial_print_unsigned(const char* s, const uint32_t number);
static void Serial_print_signed(const char* s, const int32_t number);
static void init_serial();
static void write_byte(const char data);

Serial new_Serial()
{
	Serial self;
	self.print = Serial_print;
	self.print = Serial_println;
	self.print_unsigned = Serial_print_unsigned;
	self.print_signed = Serial_print_signed;
	init_serial();
	return self;
}

static void Serial_print(const char* s)
{
	for (uint16_t i = 0; s[i] != '\0'; i++)
	{
		write_byte(s[i]);
		if (s[i] == '\n') write_byte('\r');
	}
	
	write_byte('\0');
	return;
}

static void Serial_println(const char* s)
{
	for (uint16_t i = 0; s[i] != '\0'; i++)
	{
		write_byte(s[i]);
		if (s[i] == '\n') write_byte('\r');
	}
	
	write_byte('\n');
	write_byte('\0');
	return;
}

static void Serial_print_unsigned(const char* s, const uint32_t number)
{
	char text[SIZE];
	text[0] = '\0';
	sprintf(text, s, number);
	Serial_print(text);
	return;
}

static void Serial_print_signed(const char* s, const int32_t number)
{
	char text[SIZE];
	text[0] = '\0';
	sprintf(text, s, number);
	Serial_print(text);
	return;
}

static void init_serial()
{
	UCSR0B = (1 << TXEN0);
	UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01));
	UBRR0 = 103;
	write_byte('\r');//write_byte('\r'); //Skicka ett vagnreturstecken, så att första utskriften hanmnar längst till vänster
	write_byte('\0');//write_byte('\0');
	return;
}

static void write_byte(const char data)
{
	while ((UCSR0A & (1 << UDRE0)) == 0) ;
	UDR0 = data;
	return;
}