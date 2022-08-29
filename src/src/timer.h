#ifndef TIMER_H_
#define TIMER_H_

#include "definitions.h"

#define INTERRUPT_TIME 16.384f // 16.384 ms mellan varje timergenererat avbrott.

typedef enum {TIMER0 = 0, TIMER1 = 1, TIMER2 = 2} TimerSelect;

typedef struct Timer
{
	bool enabled;
	volatile uint8_t executed_interrupts;
	uint8_t required_interrupts;
	TimerSelect timerselect;
	void (*on)(struct Timer*);
	void (*off)(struct Timer*);
	void (*toggle)(struct Timer*);
	void (*count)(struct Timer*);
	bool (*elapsed)(struct Timer*);
} Timer;

Timer new_timer(const TimerSelect timerselect, const uint16_t delay_time);
#endif /* TIMER_H_ */