/* Include directive */
#include "header.h"

static uint16_t ADC_read();

/**
 * @brief Prints temperature in celcius based on a fixed equation.
 * Converts ADC result to a percentage of reference voltage.
 * Celcius = 100 * Uin - 50. 
 * 
 */
void print_temp()
{
	const uint16_t ADC_result = ADC_read();
	const float Uin = Vcc * ((float)ADC_result / ADC_MAX);
	const int temperature = (int)(100 * Uin - 50);
	serial.print_signed("\nActual temp: %d celcius\n", temperature);
	return;
}

/**
 * @brief Completes a AD conversion and returns the value of
 * voltage read from the temperature sensor TMP36
 * 
 * @return double, a decimal number between 0 to 5.
 */
double ADC_return()
{
	const uint16_t ADC_result = ADC_read();
	const float Uin = Vcc * ((float)ADC_result / ADC_MAX);
	return Uin;
}

/**
 * @brief Completes a analog to digital conversion and returns the digital
 * value. Uses the macro TEMP_SENSOR for analog pin to read.
 * 
 * @return uint16_t Value between 0-1023, devide by 1023 to get percentage
 * and multiply by reference voltage (5V)
 */
static uint16_t ADC_read()
{
	ADMUX = ((1 << REFS0) | TEMP_SENSOR);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return ADC;
}