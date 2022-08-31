#include "header.h"

static uint16_t ADC_read();

/************************************************************************************************
 * Formler för beräkning av temperatur:
 * Analog inspänning Uin:
 * Uin = Vcc * ADC_result / ADC_max,
 * där ADC_result är resultatet från senaste AD-omvandling (0 - 1023).
 *
 * Temperatur temp i grader Celcius:
 * temp = 100 * Uin - 50,
 * där Uin är den beräknade analoga inspänningen (0 - 5 V).
 ************************************************************************************************/

void print_temp()
{
	const uint16_t ADC_result = ADC_read();
	const float Uin = Vcc * ((float)ADC_result / ADC_MAX);
	const int temperature = (int)(100 * Uin - 50);
	serial.print_signed("\nActual temp: %d celcius\n", temperature);
	// serial.print_decimal("\nActual temp: %lf celcius\n", temperature);
	return;
}

double ADC_return()
{
	const uint16_t ADC_result = ADC_read();
	const float Uin = Vcc * ((float)ADC_result / ADC_MAX); // 304 / 1023  = 0.29 = 1,48 V
	serial.print_decimal("mV:  %d.%d\n", Uin);

	return Uin;
}

static uint16_t ADC_read()
{
	ADMUX = ((1 << REFS0) | TEMP_SENSOR);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0)
		;
	ADCSRA = (1 << ADIF);
	return ADC;
}