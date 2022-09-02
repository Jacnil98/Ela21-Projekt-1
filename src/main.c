#include "header.h"

int main(void)
{
  setup();
  const double yref[] = {14, 18, 22, 26, 30 };
  const double x[] = {0.64, 0.68, 0.72, 0.76, 0.8 };
  lin_reg_new(&l1);
  set_training_data(&l1, x, yref, 5, 10000, 0.1);
  train_legs(&l1);
  
  while (true)
  {
    
  }
  return 0;
}