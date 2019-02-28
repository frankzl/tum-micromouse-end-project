/*
 * File:   pidFunctions.c
 * Author: frankzl
 *
 * Created on February 15, 2019, 11:18 AM
 */

#include "pidFunctions.h"

void pid_init(pid_ctrl *pid)
{
    //pid_set_gains(pid, 1.49, 0.1, .5);
    pid_set_gains(pid, 7, 1, 0);
    
    pid->integrator = 0.;
    pid->previous_error = 0.;
    pid->integrator_limit = 10000;
    pid->frequency = 1.;
}

void pid_set_gains(pid_ctrl *pid, float kp, float ki, float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

float pid_process(pid_ctrl *pid, float error)
{
    float output;
    pid->integrator += error;
    
    if (pid->integrator > pid-> integrator_limit){
        pid->integrator = pid->integrator_limit;
    } else if (pid->integrator < -pid->integrator_limit){
        pid->integrator = - pid->integrator_limit;
    }
    
    output =   - pid->kp * error;
    output +=  - pid->ki * pid->integrator / pid->frequency;
    output +=  - pid->kd * (error - pid->previous_error) * pid->frequency;
    
    pid->previous_error = error;
    return output;
}