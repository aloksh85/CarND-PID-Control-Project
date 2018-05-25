#ifndef PID_H
#define PID_H
#include <vector>
#include <algorithm>
#include  <iostream>
class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  double prev_cte;
  std::vector<double> dp;
  bool prev_twiddle_positive;
  bool prev_twiddle_negative;
  double best_error;
  int n_cycle;
  double dp_tol;
  int tweak_index;
  double total_error;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError(const double& );

  /*
  * Grid search for optimal gains
  *
  */
  void Twiddle(const double& cte);
};

#endif /* PID_H */
