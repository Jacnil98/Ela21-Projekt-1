#ifndef TIMER_H_
#define TIMER_H_

/* Includefiles: */
#include "definitions.h"

/* Time between interrupts */
#define INTERRUPT_TIME 16.384f

/* Typedef to select timer */
typedef enum {TIMER0 = 0, TIMER1 = 1, TIMER2 = 2} TimerSelect;

/**
 * @brief type definition of the struct Timer
 * 
 * @param enabled
 * @param executed_interrupts
 * @param required_interrupts
 * @param timerselect
 * 
 */
typedef struct Timer
{
	bool enabled;
	volatile uint32_t executed_interrupts;
	uint32_t required_interrupts;
	TimerSelect timerselect;
	void (*on)(struct Timer*);
	void (*off)(struct Timer*);
	void (*toggle)(struct Timer*);
	void (*count)(struct Timer*);
	void (*clear)(struct Timer*);
	
	bool (*elapsed)(struct Timer*);
	bool (*elapsed_clear)(struct Timer*);
	void (*update)(struct Timer*, uint32_t value);
} Timer;

/* External functions */

Timer new_timer(const TimerSelect timerselect, const uint32_t delay_time);
#endif /* TIMER_H_ */
