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

  prev_twiddle_negative = false;
  prev_twiddle_negative = false;
  for (int i = 0;i < 3; ++i)
    dp.push_back(0.005);

  best_error = 1000000.0;
  n_cycle = 0;
  dp_tol = 0.00001;
  tweak_index = 0;
  total_error = 0.0;
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
  ++n_cycle ;


/*  if(n_cycle  > 100) {

    double sum_dp = 0.0;
    for(const auto& g : dp) {
      sum_dp+=g;
    }
    std::cout<<"dp sum : "<< sum_dp<<", dp_tol: "<<dp_tol<<std::endl;
    if(sum_dp > dp_tol) {
      Twiddle(cte);
    }
  }
  */
}

double PID::TotalError(const double& cte) {
  total_error+= pow(cte,2);
  return total_error;
}


void PID::Twiddle(const double& cte) {
 std::cout<<"============== TWIDDLING============="<<std::endl;
  double error = TotalError(cte)/n_cycle;

  if(!prev_twiddle_negative && !prev_twiddle_positive) {
    best_error = error;
    if(tweak_index ==0)
    {
      Kp+=dp[tweak_index];
      prev_twiddle_positive = true;
    }
    if(tweak_index ==1)
    {
      Ki+=dp[tweak_index];
      prev_twiddle_positive = true;
    }
    if(tweak_index ==2)
    {
      Kd+=dp[tweak_index];
      prev_twiddle_positive = true;
    }

    return;
  }

  if (error < best_error) {
    best_error = error;
    dp[tweak_index]*= 1.1;
    tweak_index = (tweak_index+1)%3;
    prev_twiddle_negative = false;
    prev_twiddle_positive = false;

    return;

  }
  else {
    if(prev_twiddle_positive && !prev_twiddle_negative)
    {
      prev_twiddle_negative = true;
      if(tweak_index ==0)
      {
        Kp+=-2.0*dp[tweak_index];
        prev_twiddle_positive = true;
      }
      if(tweak_index ==1)
      {
        Ki+=-2.0*dp[tweak_index];
        prev_twiddle_positive = true;
      }
      if(tweak_index ==2)
      {
        Kd+=-2.0*dp[tweak_index];
        prev_twiddle_positive = true;
      }
    }
    else if( prev_twiddle_negative && prev_twiddle_positive){
      if(tweak_index ==0)
      {
        Kp+=dp[tweak_index];
      }
      else if(tweak_index ==1)
      {
        Ki+=dp[tweak_index];
      }
      else if(tweak_index ==2)
      {
        Kd+=dp[tweak_index];
      }
      dp[tweak_index]*=0.9;
      tweak_index = (tweak_index+1)%3;
      prev_twiddle_negative = false;
      prev_twiddle_positive = false;
    }
  }
}
