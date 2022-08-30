#include "header.h"

int main(void)
{
  setup();
  const double x[] = {-12.5, 0, 25, 50, 90 };
  const double yref[] = {0.4, 0.5, 0.75, 1, 1,4 };
  timer1 = new_timer(TIMER1, 300);
  lin_reg_new(&l1);
  set_training_data(&l1, x, yref, 5, 10000, 0.1);
  train_legs(&l1);

  while (true)
  {
    
  }
  
  return 0;
}