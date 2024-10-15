#include "pid.h"

void pid_compute(struct pid_controller_t *pid, uint32_t current_millis, double input)
{
  int32_t time_change = (current_millis - pid->last_time);
  if (time_change >= pid->sample_time)
  {
    /*Compute all the working error variables*/
    double error = pid->setpoint - input;
    pid->i_term += (pid->ki * error);
    if (pid->i_term > pid->out_max)
    {
      pid->i_term = pid->out_max;
    }
    else if (pid->i_term < pid->out_min)
    {
      pid->i_term = pid->out_min;
    }
    double dInput = (input - pid->last_input);
    /*Compute PID Output*/
    pid->output = pid->kp * error + pid->i_term - pid->kd * dInput;
    if (pid->output > pid->out_max)
    {
      pid->output = pid->out_max;
    }
    else if (pid->output < pid->out_min)
    {
      pid->output = pid->out_min;
    }
    /*Remember some variables for next time*/
    pid->last_input = input;
    pid->last_time = current_millis;
  }
}

void pid_init_controller(struct pid_controller_t *pid)
{
  pid->i_term = 0.0f;
  pid->output = 0.0f;
  pid->setpoint = 0.0f;
  pid->last_time = 0.0f;
  pid->sample_time = 10;
  pid->out_min = 0.0f;
  pid->out_max = 100.0f;
  pid->last_input = 0.0f;
}

void pid_set_current_time(struct pid_controller_t *pid, int32_t millis)
{
  pid->last_time = millis;
}

void pid_set_sample_time(struct pid_controller_t *pid, int32_t new_sample_time)
{
  if (new_sample_time > 0)
  {
    double ratio = (double)new_sample_time / (double)pid->sample_time;
    pid->ki *= ratio;
    pid->kd /= ratio;
    pid->sample_time = (uint32_t)new_sample_time;
  }
}

void pid_set_tunings(struct pid_controller_t *pid, double kp, double ki, double kd)
{
  // double sample_time_in_sec = ((double)pid->sample_time) / 1000.0f;
  pid->kp = kp;
  pid->ki = ki; // sample_time_in_sec;
  pid->kd = kd; // sample_time_in_sec;
}

void pid_set_output_limits(struct pid_controller_t *pid, double min, double max)
{
  if (min > max)
  {
    return;
  }
  pid->out_min = min;
  pid->out_max = max;
  if (pid->output > pid->out_max)
  {
    pid->output = pid->out_max;
  }
  else if (pid->output < pid->out_min)
  {
    pid->output = pid->out_min;
  }
  if (pid->i_term > pid->out_max)
  {
    pid->i_term = pid->out_max;
  }
  else if (pid->i_term < pid->out_min)
  {
    pid->i_term = pid->out_min;
  }
}

void pid_set_setpoint(struct pid_controller_t *pid, double value)
{
  pid->setpoint = value;
}

double pid_get_output(struct pid_controller_t *pid)
{
  return pid->output;
}
