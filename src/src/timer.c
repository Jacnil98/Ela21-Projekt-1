#include "Timer.h"

static void Timer_on(Timer *self);
static void Timer_off(Timer *self);
static void Timer_toggle(Timer *self);
static void Timer_count(Timer *self);
static void Timer_clear(Timer *self);
static bool Timer_elapsed(Timer *self);
static bool Timer_elapsed_clear(Timer *self);
static void Timer_update(Timer *self, uint32_t value);

/**
 * @brief Creates a new instance of structure Timer which is used in the 
 * AVR interrupt service routines. All timers have the same prescaler of 16M/1024.
 * TIMER1 is in CTC-mode and is set to count to the same value as the overflow timers.
 * 
 * @example Timer timer0 = new_Timer(TIMER0, 1000) - Timer0 set to count to 1 second.
 * 
 * @param timerselect Selection between enumeration of timers, TIMER0, TIMER1, TIMER2.
 * @param delay_time time in milliseconds.
 * @return Timer instance of Timer-struct
 */
Timer new_timer(const TimerSelect timerselect, const uint32_t delay_time)
{
	Timer self;
	self.enabled = false;
	self.executed_interrupts = 0x00;
	self.required_interrupts = (uint32_t)((float)delay_time / INTERRUPT_TIME + 0.5);
	self.timerselect = timerselect;
	
	if (self.timerselect == TIMER0)
		TCCR0B = ((1 << CS00) | (1 << CS02));
	else if (self.timerselect == TIMER1)
	{
		TCCR1B = ((1 << CS10) | (1 << CS12) | (1 << WGM12));
		OCR1A = 256;
	}
	else if (self.timerselect == TIMER2)
		TCCR2B = ((1 << CS20) | (1 << CS21) | (1 << CS22));

	self.on = Timer_on;
	self.off = Timer_off;
	self.toggle = Timer_toggle;
	self.count = Timer_count;
	self.update = Timer_update;
	self.elapsed = Timer_elapsed;
	return self;
}

/**
 * @brief Turns on the instance of timer.
 * 
 * @param self pointer to Timer instance
 */
static void Timer_on(Timer *self)
{
	if (self->timerselect == TIMER0)
		TIMSK0 = (1 << TOIE0);
	else if (self->timerselect == TIMER1)
		TIMSK1 = (1 << OCIE1A);
	else if (self->timerselect == TIMER2)
		TIMSK2 = (1 << TOIE2);
	self->enabled = true;
	return;
}

/**
 * @brief Turns off the instance of timer.
 * 
 * @param self pointer to Timer instance
 */
static void Timer_off(Timer *self)
{
	if (self->timerselect == TIMER0)
		TIMSK0 = 0x00;
	else if (self->timerselect == TIMER1)
		TIMSK1 = 0x00;
	else if (self->timerselect == TIMER2)
		TIMSK2 = 0x00;
	self->enabled = false;
	return;
}

/**
 * @brief Toggles the instance of timer on/off.
 * 
 * @param self pointer to Timer instance
 */
static void Timer_toggle(Timer *self)
{
	if (self->enabled)
		self->off(self);
	else
		self->on(self);
	return;
}

/**
 * @brief Counter for the timer, used in the interrupt service routine.
 * 
 * @param self pointer to Timer instance
 */
static void Timer_count(Timer *self)
{
	if (self->enabled)
		self->executed_interrupts++;
	return;
}

/**
 * @brief Clears the number of executed interrupts.
 * 
 * @param self pointer to Timer instance
 */
static void Timer_clear(Timer *self)
{
	if (self->enabled)
		self->executed_interrupts = 0x00;
	return;
}

/**
 * @brief Checks if the timer has elapsed by comparing executed interrupts
 * with required interrupts and if it returns true.
 * @details DOES NOT RESET EXECUTED INTERRUPTS -> call for Timer_clear.
 * 
 * @param self pointer to Timer struct.
 * @return true if timer has elapsed.
 * @return false if timer has NOT elapsed.
 */
	static bool Timer_elapsed(Timer *self)
{
	if (self->executed_interrupts >= self->required_interrupts)
	{
		return true;
	}
	else
		return false;
}

/**
 * @brief Checks if the timer has elapsed by comparing executed interrupts
 * with required interrupts and if it returns true, it also clears variable
 * executed interrupts.
 * 
 * @param self pointer to Timer instance
 * @return true if timer has elapsed.
 * @return false if timer has NOT elapsed.
 */
static bool Timer_elapsed_clear(Timer *self)
{
	if (self->executed_interrupts >= self->required_interrupts)
	{
		self->executed_interrupts = 0x00;
		return true;
	}
	else
		return false;
}

/**
 * @brief Updates the variable required interrupts. Used for
 * changing the adaptive timer through average value from Array struct.
 * 
 * @param self pointer to Timer instance
 * @param value number of required interrupts for timer interrupt service routine.
 */
static void Timer_update(Timer *self, uint32_t value)
{
	self->required_interrupts = value;
}
