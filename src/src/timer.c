#include "timer.h"

static void Timer_on(Timer *self);
static void Timer_off(Timer *self);
static void Timer_toggle(Timer *self);
static void Timer_count(Timer *self);
static bool Timer_elapsed(Timer *self);
static void Timer_update(Timer *self, uint32_t value);

Timer new_timer(const TimerSelect timerselect, const uint32_t delay_time)
{
	Timer self;
	self.enabled = false;
	self.executed_interrupts = 0x00;
	self.required_interrupts = (uint32_t)((float)delay_time / INTERRUPT_TIME + 0.5);
	self.timerselect = timerselect;
/* VILKEN PRESCALER */
	if (self.timerselect == TIMER0)
		TCCR0B = ((1 << CS00) | (1 << CS02));
/* VILKEN PRESCALER */
	else if (self.timerselect == TIMER1)
	{
		TCCR1B = ((1 << CS10) | (1 << CS12) | (1 << WGM12));
		OCR1A = 256;
	}
/* VILKEN PRESCALER */
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

static void Timer_toggle(Timer *self)
{
	if (self->enabled)
		self->off(self);
	else
		self->on(self);
	return;
}

static void Timer_count(Timer *self)
{
	if (self->enabled)
		self->executed_interrupts++;
	return;
}

static bool Timer_elapsed(Timer *self)
{
	if (self->executed_interrupts >= self->required_interrupts)
	{
		self->executed_interrupts = 0x00;
		return true;
	}
	else
		return false;
}

static void Timer_update(Timer *self, uint32_t value)
{
	self->required_interrupts = value;//(uint32_t)((float)value / INTERRUPT_TIME + 0.5);
}
