#include "header.h"
#include "lin_reg.h"

int main(void)
{

  const double x[] = {-12.5, 0, 25, 50, 90 };
  const double yref[] = {0.4, 0.5, 0.75, 1, 1,4 };
  lin_reg_new(&l1);
  lin_reg_set_training_data(&l1, x, yref, 5, 10000, 0.1);
  
  setup();

  while (true)
  {
    
  }
  
  return 0;
}