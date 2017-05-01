#include "PID.h"

/*
* TODO: Complete the PID class.
*/

PID::PID(double Kp, double Ki, double Kd): Kp(Kp), Ki(Ki), Kd(Kd) {

}

PID::~PID() {}

void PID::UpdateError(double cte) {
  number_of_steps++;
  d_error = cte - p_error; // p_error is the last cte.
  p_error = cte;
  i_error += cte;
}

double PID::TotalError() {

}

void PID::ParameterOptimization() {

}
