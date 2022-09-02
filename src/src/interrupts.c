#include "header.h"



/**
 * @brief Interrupt protocol for PCINT0, specifically for PINB, BUTTON.
 * Enables the counting timer, timer1, on initial button interrupt.
 * Following interrupts pushes the current value from timer1 to array
 * to adjust the adaptive time on timer2.
 * 
 * @short Debounce function present.
 */
ISR(PCINT0_vect)
{
	PCICR = 0x00;
	timer0.on(&timer0);

	if (PINB & (1 << BUTTON))
	{
		if (!timer1.enabled)
		{
			timer1.on(&timer1);
		}
		else
		{
			arr.push(&arr, timer1.executed_interrupts);
			timer2.update(&timer2, arr.average(&arr));
			timer1.executed_interrupts = 0x00;
		}
		timer2.executed_interrupts = 0x00;
		serial.print_decimal("\nPredicted temperature: %d.%d\n", predict(&l1, ADC_return()));
	}
	return;
}

/*
 * Debounce timer
 */
ISR(TIMER0_OVF_vect)
{
	timer0.count(&timer0);

	if (timer0.elapsed(&timer0))
	{
		PCICR = (1 << PCIE0);
		timer0.off(&timer0);
		timer0.executed_interrupts = 0x00;
	}
	return;
}

ISR(TIMER1_COMPA_vect)
{
	timer1.count(&timer1);
	if (timer1.elapsed(&timer1))
	{
		arr.push(&arr, timer1.executed_interrupts);
		timer1.executed_interrupts = 0x00;
		timer2.update(&timer2, arr.average(&arr));
	}
	return;
}

ISR(TIMER2_OVF_vect)
{	
	timer2.count(&timer2);
	if (timer2.elapsed(&timer2))
	{
		arr.print(&arr);
		serial.print("--\n");
		serial.print_decimal("\nPredicted Temperature: %d.%d\n", predict(&l1, ADC_return()));
		serial.print("\n--\n");
	}
}