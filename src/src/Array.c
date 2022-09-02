#include "header.h"

/* Static functions */

static void push(Array *self, const uint32_t data);
static void pop(Array *self);
static void clear(Array *self);
static void print(Array *self);
static uint32_t average(Array *self);
static inline void init_array(uint32_t *data, const uint8_t size);


/**
 * @brief new_Array - creates object of struct Array and initiates 
 * values and function pointers.
 * 
 * @return Array 
 */
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

/**
 * @brief push - Adds data to element in array
 * 
 * @param self array struct
 * @param data Value to add onto the next element in array.
 */
static void push(Array *self, const uint32_t data)
{
    self->data[self->next++] = data;
    if (self->elements < ARRAY_SIZE)
        self->elements++;
    if (self->next >= ARRAY_SIZE)
        self->next = 0;
    return;
}

/**
 * @brief pop - Deletes the last element of the array
 * 
 * @param self array struct
 */
static void pop(Array *self)
{
    if (!self->elements)
        return;
    if (!self->next)
        self->next = ARRAY_SIZE - 1;
    else
        self->next--;
    self->data[self->next] = 0;
    self->elements--;
    return;
}


/**
 * @brief clear - Clears the array
 * 
 * @param self array struct
 */
static void clear(Array *self)
{
    init_array(self->data, ARRAY_SIZE);
    self->elements = 0;
    self->next = 0;
    return;
}

/**
 * @brief print - Prints out the average value of the array
 * 
 * @param self array struct
 */
static void print(Array *self)
{
    if (!self->elements)
        return;

    /* serial.print_unsigned("Elements present: %d\n", self->elements);
    for (register uint8_t i = 0; i < self->elements; i++)
        serial.print_unsigned("Value: %d\n", self->data[i]); */
    serial.print_unsigned("\nTime in s: %d\n\n", (uint16_t)((float)16.384 * average(self) / 1000) + 0.5);
}

/**
 * @brief average - Calculates the average value of the array
 * 
 * @param self array struct
 * @return uint32_t - the average value of the sum divided by number of elements.
 */
static uint32_t average(Array *self)
{
    uint32_t sum = 0;
    for (register uint8_t i = 0; i < self->elements; i++)
    {
        sum += self->data[i];
    }
    return sum / (double)self->elements;
}

/**
 * @brief init_array - sets start value 0 to all index positions in object
 * 
 * @param data Pointer to the arrays data to initiate.
 * @param size Numbers of elements in the array
 */
static inline void init_array(uint32_t *data, const uint8_t size)
{
    for (register uint8_t i = 0; i < size; i++)
    {
        data[i] = 0;
    }
    return;
}