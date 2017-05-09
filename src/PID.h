#ifndef PID_H
#define PID_H

#include <cmath>

enum TWIDDLE_MODE {
  WAIT,
  COLLECT,
  OPTIMIZE,
  CHECK
};

enum TWIDDLE_PARAMETER {
  P = 0,
  I = 1,
  D = 2
};

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
  * Constructor
  */
  PID(double Kp, double Ki, double Kd, int initial_iterations);

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


private:
  void ExecuteTwiddleIteration(double cte);

  /**
   * Number of iterations to wait before beginning optimizing.
   */
  int initial_iterations_;

  int processed_iterations_ = 0;

  double best_error_ = INFINITY;

  /**
   * Current mode.
   */
  TWIDDLE_MODE twiddle_mode_ = WAIT;

  /**
   * Current parameter
   */
  TWIDDLE_PARAMETER twiddle_parameter = P;

  /**
   * Change in P threshold.
   */
  double dp_threshold_ = 0.001;

  /**
   * Array to measure the change in P.
   */
  double dp_[3] = {0.0005, 0.00005, 0.015};

  void GoToNextTwiddleParameter();
};

#endif /* PID_H */
