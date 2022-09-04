#include "header.h"

/**
 * @authors Jacob Nilsson & Jacob Lundkvist. 
 * 
 * 
 * @brief Construct a linear regression that predicts the value
 * on a temperature sensor. If a button (that is connected to Pin 13)
 * is pressed the predicted temeperature is printed. The time between
 * each press is stored in an array. The array calcultates the average
 * value and updates the timer that prints out the predicted temp.
 * 
 */
int main(void)
{
  setup();
  const double yref[] = {14, 18, 22, 26, 30 };
  const double x[] = {0.64, 0.68, 0.72, 0.76, 0.8 };
  lin_reg_new(&l1);
  set_training_data(&l1, x, yref, 5, 10000, 0.1);
  train_regression_model(&l1);
  
  while (true)
  {
    
  }
  return 0;
}