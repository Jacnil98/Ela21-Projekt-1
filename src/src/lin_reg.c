#include "header.h"

static void optimize(struct lin_reg* self, const double input, const double reference);
static void shuffle(struct lin_reg* self);
static inline double get_random(void) { return rand() / (double)RAND_MAX; }

void lin_reg_new(struct lin_reg* self)
{
   self->x = 0;
   self->yref = 0;
   self->num_sets = 0;
   self->epoch = 0;
   self->lr = 0;

   self->bias = get_random();
   self->weight = get_random();
   serial.print_decimal("Initial bias: %d.%d\n\n", self->bias);
   serial.print_decimal("Initial Weight: %d.%d\n\n", self->weight);

   return;
}

void set_training_data(struct lin_reg* self, const double* x, const double* yref, const uint8_t num_sets,const size_t epoch,const double lr)
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

   // self->num_sets = num_sets > NUM_SETS ? NUM_SETS : num_sets;

   for (uint8_t i = 0; i < self->num_sets; ++i)
   {
      self->train_order[i] = i; // Lagrar index för varje träningsuppsättning
   }

   return;
}

void train_legs(struct lin_reg* self)
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
   serial.print("Training done\n");
   return;
}

static void optimize(struct lin_reg* self, const double input, const double reference)
{
   const double prediction = self->weight * input + self->bias;
   const double deviation = reference - prediction;
   const double change_rate = deviation * self->lr;

   self->bias += change_rate;
   self->weight += change_rate * input;

   return;
}

static void shuffle(struct lin_reg* self)
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

//Predikerar värdet med hjälp av de uträknade värderna
double predict(const struct lin_reg* self, const double input)
{
   serial.print_decimal("Weight: %d.%d\n", self->weight);
   serial.print_decimal("Bias: %d.%d\n",self->bias);
   return (self->weight * input + self->bias);
}

 