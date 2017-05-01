#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error = 0.0;
  double i_error = 0.0;
  double d_error = 0.0;
  double total_error = 0.0;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
   * Tracking
   */
  int number_of_steps = 0;

  /*
  * Constructor
  */
  PID(double Kp, double Ki, double Kd);

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
   * Twiddle
   */
  void ParameterOptimization();
};

#endif /* PID_H */
