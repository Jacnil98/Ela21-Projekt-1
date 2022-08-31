#ifndef ARRAY_H_
#define ARRAY_H_

#include "definitions.h"

#define SIZE 5

typedef struct Array
{
    size_t data[SIZE];
    uint8_t elements;
    uint8_t next;
    void (*push)(struct Array*, size_t);
    void (*pop)(struct Array*);
    void (*clear)(struct Array*);
    void (*print)(const struct Array*);
    size_t (*average)(const struct Array*);
} Array;

Array new_Array(void);

#endif /* ARRAY_H_ */