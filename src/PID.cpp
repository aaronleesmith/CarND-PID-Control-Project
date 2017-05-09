#include "PID.h"
#include <cmath>
#include <iostream>

PID::PID(double Kp, double Ki, double Kd, int initial_iterations): Kp(Kp), Ki(Ki), Kd(Kd), initial_iterations_(initial_iterations) {

}

PID::~PID() {}

void PID::UpdateError(double cte) {
  std::cout << "Iteration #" << processed_iterations_  << std::endl;

  processed_iterations_++;

  d_error = cte - p_error; // p_error is the last cte.
  p_error = cte;
  i_error += cte;

  ExecuteTwiddleIteration(cte);
}

double PID::TotalError() {
  return -(Kp * p_error + Kd * d_error + Ki * i_error);
}

void PID::ExecuteTwiddleIteration(double cte) {
  total_error += pow(TotalError(), 2);


  /**
   * If we are still in the initial data collection phase, leave immediately.
   */
  if (processed_iterations_ < initial_iterations_) {
    return;
  } else if (processed_iterations_ >= initial_iterations_ && twiddle_mode_ == WAIT) {
    twiddle_mode_ = COLLECT;
  }

  if (dp_[0] + dp_[1] + dp_[2] < dp_threshold_) {
    std::cout << "Done twiddling: " << best_error_ << std::endl;
    return;
  } else {
    std::cout << "Best twiddle error: " << best_error_ << std::endl;
    std::cout << "Sum of dp: " << dp_[0] + dp_[1] + dp_[2] << std::endl;
  }

  if (twiddle_mode_ == COLLECT) {
    switch(twiddle_parameter) {
      case P:
        Kp += dp_[(int) P];
        break;
      case I:
        Ki += dp_[(int) I];
        break;
      case D:
        Kd += dp_[(int) D];
        break;
    }

    twiddle_mode_ = OPTIMIZE;
  } else if (twiddle_mode_ == OPTIMIZE) {
    double error = TotalError();
    if (error < best_error_) {
      best_error_ = error;
      dp_[(int) twiddle_parameter] *= 1.1;
      GoToNextTwiddleParameter();
      twiddle_mode_ = COLLECT;
    } else {
      switch(twiddle_parameter) {
        case P:
          Kp -= 2*dp_[(int) P];
          break;
        case I:
          Ki -= 2*dp_[(int) I];
          break;
        case D:
          Kd -= 2*dp_[(int) D];
          break;
      }

      twiddle_mode_ = CHECK;
    }
  } else if (twiddle_mode_ == CHECK) {
    double error = TotalError();
    if (error < best_error_) {
      best_error_ = error;
      dp_[(int) twiddle_parameter] *= 1.05;
    } else {
      switch(twiddle_parameter) {
        case P:
          Kp += dp_[(int) P];
          break;
        case I:
          Ki += dp_[(int) I];
          break;
        case D:
          Kd += dp_[(int) D];
          break;
      }

      dp_[(int) twiddle_parameter] *= 0.95;
    }

    GoToNextTwiddleParameter();
    twiddle_mode_ = COLLECT;
    return;
  }
}

void PID::GoToNextTwiddleParameter() {
  switch(twiddle_parameter) {
    case P:
      twiddle_parameter = I;
      break;
    case I:
      twiddle_parameter = D;
      break;
    case D:
      twiddle_parameter = P;
      break;
  }
}

