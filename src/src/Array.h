#ifndef ARRAY_H_
#define ARRAY_H_

#include "definitions.h"

#define ARRAY_SIZE 5

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

Array new_Array(void);

#endif /* ARRAY_H_ */