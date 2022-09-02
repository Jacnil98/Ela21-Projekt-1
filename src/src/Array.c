#include "header.h"

static void push(Array* self, const uint32_t new_elements);
static void pop(Array* self);
static void clear(Array* self);
static void print(Array* self);
static uint32_t average(Array* self);
static inline void init_array(uint32_t* data, const uint8_t size);

Array new_Array(void)
{
    Array self;
    self.elements = 0;
    self.next = 0;
    self.push = push;
    self.pop = pop;
    self.clear = clear;
    self.print = print;
    self.average = average;
    init_array(self.data, ARRAY_SIZE);
    return self;
}

static void push(Array* self, const uint32_t new_element)
{
    self->data[self->next++] = new_element;
    if (self->elements < ARRAY_SIZE)
        self->elements++;
    if (self->next >= ARRAY_SIZE)
        self->next = 0;
    return;
}

static void pop(Array* self)
{
    if (!self->elements)
        return;
    if (!self->next)
        self->next = ARRAY_SIZE-1;
    else
        self->next--;
    self->data[self->next] = 0;
    self->elements--;
    return;
}

static void clear(Array* self)
{
    init_array(self->data, ARRAY_SIZE);
    self->elements = 0;
    self->next = 0;
    return;
}

static void print(Array* self)
{
    if (!self->elements) return;
    
    /* serial.print_unsigned("Elements present: %d\n", self->elements);
    for (register uint8_t i = 0; i < self->elements; i++)
        serial.print_unsigned("Value: %d\n", self->data[i]); */
    serial.print_unsigned("\nTime in s: %d\n\n", (uint16_t)((float)16.384*average(self)/1000)+0.5);
}

static uint32_t average(Array* self)
{
    uint32_t value = 0;
    for( register uint8_t i = 0; i < self->elements; i++)
    {
        value += self->data[i];
    }
    return value/(double)self->elements;
}

static inline void init_array(uint32_t* data, const uint8_t size)
{
    for(register uint8_t i = 0; i < size; i++)
    {
        data[i] = 0;
    }
    return;
}