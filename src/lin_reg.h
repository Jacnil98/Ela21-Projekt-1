#ifndef LIN_REG_H_
#define LIN_REG_H_

/* Include directive. */
#include "definitions.h"

/* Defines maximum value och sets. */
#define NUM_SETS 20

/**
 * @brief type definition of the struct lin_reg
 *
 * @param x Training data (X-axis).
 * @param yref Reference training data (Y-axis).
 * @param train_order The order in which the current epoch is optimized.
 * @param num_sets Number of sets (Number of values in training data).
 * @param bias Offset the Y-axis interception.
 * @param weight The coefficient for regression data.
 * @param epoch number of training epochs.
 * @param lr learning rate.
 * @param training_done Indicates when training is done.
 *
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
   bool training_done;
} lin_reg;

/* External functions */

void lin_reg_new(lin_reg* self);
void set_training_data(lin_reg* self, const double* x, const double* yref, const uint8_t num_sets, const size_t epoch,const double lr);
void train_regression_model(lin_reg* self);
double predict(const lin_reg* self, const double input);

#endif /* LIN_REG_H_ */