#include "header.h"

ISR (PCINT0_vect)
{
	PCICR = 0x00;
	TIMSK0 = (1 << TOIE0);

	if (PINB & (1 << BUTTON)) 
	{
		serial.print_signed("yo",predict(&l1,ADC_return()));
	}
	return;
}

ISR (TIMER0_OVF_vect)
{
	executed_interrupts++;
	
	if(executed_interrupts >= 12)
	{
		TIMSK0 = 0x00;
		PCICR = (1 << PCIE0);
		executed_interrupts = 0x00;
	}
	return;
}