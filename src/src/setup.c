#include "header.h"
static void init_serial();
static void init_ports();
static void init_interrupts();
static void init_timers();
static void init_ADC();

void setup()
{
    init_serial(); 
    init_ports();
	init_interrupts();
	init_timers();
	init_ADC();
    return;
}

static void init_serial()
{
	serial = new_Serial();
	return;
}

static void init_ports()
{
	PORTB = (1 << BUTTON);
	return;
}

static void init_interrupts()
{
	asm("SEI");
	PCICR = (1 << PCIE0);
	PCMSK0 = (1 << PCINT5);
	return;
}

static void init_timers()
{
	timer0 = new_timer(TIMER0, 300);
	timer1 = new_timer(TIMER1, 600000);
	timer2 = new_timer(TIMER2, 60000);
	timer2.on(&timer2);
	arr = new_Array();
	return;
} 

static void init_ADC()
{
	ADMUX = ((1 << REFS0) | TEMP_SENSOR) ;
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;;
	ADCSRA = (1 << ADIF);
	return;
}