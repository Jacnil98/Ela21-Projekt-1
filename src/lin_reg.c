#include "header.h"

static void optimize(lin_reg* self, const double input, const double reference);
static void shuffle(lin_reg* self);
static inline double get_random(void) { return rand() / (double)RAND_MAX; }

/**
 * @brief Creates a new instance of the struct lin_reg which is used to
 * find the optimal formula for the linear regression.
 * 
 * @param self pointer to lin_reg instance.
 */
void lin_reg_new(struct lin_reg* self)
{
   self->x = 0;
   self->yref = 0;
   self->num_sets = 0;
   self->epoch = 0;
   self->bias = get_random();
   self->weight = get_random();
   self->lr = 0;
   self->training_done = false;

   return;
}

/**
 * @brief Sets the training data for the lin_reg object
 * 
 * @param self pointer to lin_reg instance.
 * @param x training data, pointer to static array.
 * @param yref reference data, pointer to the static array.
 * @param num_sets Number of sets (Number of values in training data).
 * @param epoch Number of epochs the model trains.
 * @param lr learning rate, decimal number between 0-1.
 */
void set_training_data(lin_reg* self, const double* x, const double* yref, const uint8_t num_sets,const size_t epoch,const double lr)
{
   self->x = x;
   self->yref = yref;
   self->epoch = epoch;
   self->lr = lr;
   
   if (num_sets > NUM_SETS)
   {
      self->num_sets = NUM_SETS;
   }
   else
   {
      self->num_sets = num_sets;
   }

   for (uint8_t i = 0; i < self->num_sets; ++i)
   {
      self->train_order[i] = i;
   }

   return;
}

/**
 * @brief Trains the regression model for the set amount of
 * epochs specified in set_training_data.
 * 
 * @param self pointer to lin_reg instance.
 */
void train_regression_model(lin_reg* self)
{
   for (size_t i = 0; i < self->epoch; i++)
   {
      shuffle(self);
      
      for (size_t j = 0; j < self->num_sets; ++j)
      {
         const size_t k = self->train_order[j];
         optimize(self, self->x[k], self->yref[k]);
      }
   }
   self->training_done = true;
   serial.print("Training done\n\n");
   serial.print_decimal("Weight: %d.%d%d\n", self->weight);
   serial.print_decimal("Bias: %d.%d%d\n\n",self->bias);
   serial.print("Start by pressing the button on pin 13.\n");
   return;
}

/**
 * @brief Omptimizes the regression formula.
 * @details Updates the bias and weight based of the 
 * change rate from the current optimization.
 * 
 * @param self pointer to lin_reg instance.
 * @param input the x value from the array.
 * @param reference the y value from the reference array.
 */
static void optimize(lin_reg* self, const double input, const double reference)
{
   const double prediction = self->weight * input + self->bias;
   const double deviation = reference - prediction;
   const double change_rate = deviation * self->lr;

   self->bias += change_rate;
   self->weight += change_rate * input;

   return;
}

/**
 * @brief Shuffles the training order.
 * @details is used so the model does not become
 * too familiar with the training data.
 * @param self pointer to lin_reg instance.
 */
static void shuffle(lin_reg* self)
{
   for (size_t i = 0; i < self->num_sets; ++i)
   {
      const size_t random = rand() % self->num_sets;
      const size_t temp = self->train_order[i];
      self->train_order[i] = self->train_order[random];
      self->train_order[random] = temp;
   }

   return;
}

/**
 * @brief Predicts the value from the temperature sensor
 * with use of the formula that is trained. 
 * 
 * @param self pointer to lin_reg instance.
 * @param input Voltage from the temeperatur sensor
 * 
 */
double predict(const lin_reg* self, const double input)
{
   return (self->weight * input + self->bias);
}

 