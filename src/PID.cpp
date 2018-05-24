#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {
  p_error = 0.0;
  d_error = 0.0;
  i_error = 0.0;
  prev_cte =0.0;
}

PID::~PID() {}

void PID::Init(double kp, double ki, double kd) {
  Kp = kp;
  Ki = ki;
  Kd = kd;
}

void PID::UpdateError(double cte) {
  p_error = cte;
  d_error = cte - prev_cte;
  i_error+= cte;

  prev_cte = cte;

}

double PID::TotalError() {
}
