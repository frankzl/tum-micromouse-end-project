#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include <xc.h> // include processor files - each processor file is guarded.
#endif	/* XC_HEADER_TEMPLATE_H */


#ifndef PID_H
#define PID_H

//The PID controller
typedef struct{
    float kp;
    float ki;
    float kd;
    float integrator;
    float previous_error;
    float integrator_limit;
    float frequency;
} pid_ctrl;

void pid_init(pid_ctrl *pid);

void pid_set_gains(pid_ctrl *pid, float kp, float ki, float kd);

float pid_process(pid_ctrl *pid, float error);

#endif