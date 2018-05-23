#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {
  p_error = 0.0;
  d_error = 0.0;
  i_error = 0.0;
}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  Kp = Kp;
  Ki = Ki;
  Kd = Kd;
}

void PID::UpdateError(double cte) {
  p_error = cte;
  d_error = cte - d_error;
  i_error+= cte;

}

double PID::TotalError() {
}
