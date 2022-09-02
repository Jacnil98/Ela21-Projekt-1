#ifndef TIMER_H_
#define TIMER_H_

/* Includefiles: */
#include "definitions.h"

/* Time between interrupts */
#define INTERRUPT_TIME 16.384f

/* Typedef to select timer */
typedef enum {TIMER0 = 0, TIMER1 = 1, TIMER2 = 2} TimerSelect;

/**
 * @brief Type definition of the struct Timer with four
 * variables and function pointers. 
 * @details All three timers avaible are set to work in
 * similar manner. Exception TIMER1 is set in CTC-mode but 
 * limited to 256 to function as the other timers that are
 * set to overflow.
 * 
 * @param enabled boolean, false when off, true when on.
 * @param executed_interrupts number of interrupts that
 * has occured through ISR and the use of Timer_count function.
 * @param required_interrupts used in functions named elapsed
 * to check if executed_interrupts >= required_interrupts.
 * @param timerselect Enumeration of the three present timers
 * in the Arduino Uno board.
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
