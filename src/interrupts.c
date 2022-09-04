#include "header.h"

/**
 * @brief Interrupt protocol for PCINT0
 * @details Specifically for PINB, BUTTON.
 * Enables the counting timer, timer1, on initial button interrupt.
 * Following interrupts pushes the current value from timer1 to array
 * to adjust the adaptive time on timer2.
 * 
 */
ISR(PCINT0_vect)
{
	PCICR = 0x00;
	timer0.on(&timer0);

	if (PINB & (1 << BUTTON) && l1.training_done)
	{
		if (!timer1.enabled)
		{
			timer1.on(&timer1);
			serial.print("Timer now initated, tracking time between button presses\n\n");
		}
		else
		{
			arr.push(&arr, timer1.executed_interrupts);
			timer2.update(&timer2, arr.average(&arr));
			timer1.clear(&timer1);
		}
		timer2.executed_interrupts = 0x00;
		serial.print("-----------------------------\n");
		serial.print_decimal("Predicted temperature: %d.%d%d\n", predict(&l1, ADC_return()));
		serial.print("-----------------------------\n\n\n");
	}
	return;
}

/**
 * @brief Debounce timer for when pin change interrupt 0 occurs.
 * Typically on for about 300 ms then enables PCICR.
 */
ISR(TIMER0_OVF_vect)
{
	timer0.count(&timer0);

	if (timer0.elapsed_clear(&timer0))
	{
		PCICR = (1 << PCIE0);
		timer0.off(&timer0);
		timer0.executed_interrupts = 0x00;
	}
	return;
}


/**
 * @brief Counts to set time after timer is started. 
 * @details When timer1 has elapsed, pushes value to 
 * array and updates timer2 followed by clearing itself.
 * 
 */
ISR(TIMER1_COMPA_vect)
{
	timer1.count(&timer1);
	if (timer1.elapsed(&timer1))
	{
		arr.push(&arr, timer1.executed_interrupts);
		timer2.update(&timer2, arr.average(&arr));
		timer1.clear(&timer1);
	}
	return;
}

/**
 * @brief ISR object for TIMER2
 * @details prints the average value from array in seconds
 * and the predicted temperature based of the linear regression training.
 * 
 */
ISR(TIMER2_OVF_vect)
{	
	timer2.count(&timer2);
	if (timer2.elapsed_clear(&timer2)  && l1.training_done)
	{
		serial.print("-----------------------------\n");
		serial.print_decimal("Predicted Temperature: %d.%d%d\n", predict(&l1, ADC_return()));
		serial.print("-----------------------------\n\n\n");
	}
}