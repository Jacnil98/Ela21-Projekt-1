#ifndef LIN_REG_H_
#define LIN_REG_H_

/* Inkluderingsdirektiv: */
#include "definitions.h"

#define NUM_SETS 20

struct lin_reg
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

void lin_reg_new(struct lin_reg* self);
void set_training_data(struct lin_reg* self, const double* x, const double* yref, const uint8_t num_sets, const size_t epoch,const double lr);
void train_legs(struct lin_reg* self);
double predict(const struct lin_reg* self, const double input);

#endif /* LIN_REG_H_ */