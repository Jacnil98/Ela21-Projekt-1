#include "header.h"

static void push(Array* self, const size_t new_elements);
static void pop(Array* self);
static void clear(Array* self);
static void print(const Array* self);
static size_t average(Array* self);
static inline void init_array(size_t* data, const size_t size);



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
    init_array(self.data, SIZE);
    return self;
}

static void push(Array* self, const size_t new_element)
{
    self->data[self->next++] = new_element;
    if (self->elements < SIZE)
        self->elements++;
    if (self->next >= SIZE)
        self->next = 0;
    return;
}

static void pop(Array* self)
{
    if (!self->elements)
        return;
    if (!self->next)
        self->next = SIZE-1;
    else
        self->next--;
    self->data[self->next] = 0;
    self->elements--;
    return;
}

static void clear(Array* self)
{
    init_array(self->data, SIZE);
    self->elements = 0;
    self->next = 0;
    return;
}

static void print(const Array* self)
{
    if (!self->elements) return;
    
    serial.print_unsigned("Elements present: %d\n", self->elements);
    for (register uint8_t i = 0; i < self->elements; i++)
        serial.print_unsigned("Value: %d\n", self->data[i]);
}

static size_t average(Array* self)
{

}

static inline void init_array(size_t* data, const size_t size)
{

}
