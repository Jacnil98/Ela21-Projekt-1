#ifndef LIN_REG_H_
#define LIN_REG_H_

/* Includefiles: */
#include "definitions.h"

/* Defines maximum value och sets */
#define NUM_SETS 20

/**
 * @brief type definition of the struct lin_reg
 */
typedef struct lin_reg
{
   const double* x;
   const double* yref;
   uint8_t train_order[NUM_SETS];
   uint8_t num_sets;
   double bias;
   double weight;
   size_t epoch;
   double lr;
} lin_reg;

/* External functions */
void lin_reg_new(lin_reg* self);
void set_training_data(lin_reg* self, const double* x, const double* yref, const uint8_t num_sets, const size_t epoch,const double lr);
void train_legs(lin_reg* self);
double predict(const lin_reg* self, const double input);

#endif /* LIN_REG_H_ */