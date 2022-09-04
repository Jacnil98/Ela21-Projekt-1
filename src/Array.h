#ifndef ARRAY_H_
#define ARRAY_H_

/* Include directives */
#include "definitions.h"

/* Defines the max size of the array */
#define ARRAY_SIZE 5

/**
 * @brief type definition of the struct Array
 * 
 * @param data The information stored in the index of array.
 * @param elements Number of elements currently present in array.
 * @param next Points to the upcoming element in array.
 * 
 */
typedef struct Array
{
    uint32_t data[ARRAY_SIZE];
    uint8_t elements;
    uint8_t next;
    void (*push)(struct Array*, uint32_t);
    void (*pop)(struct Array*);
    void (*clear)(struct Array*);
    void (*print)(struct Array*);
    uint32_t (*average)(struct Array*);
} Array;

/* External functions */

Array new_Array(void);

#endif /* ARRAY_H_ */