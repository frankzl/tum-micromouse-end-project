#ifndef MOTORDRIVE_H
#define	MOTORDRIVE_H

#include <xc.h> 

#define RIGHT_WHEEL_VELO 0
#define LEFT_WHEEL_VELO 1
#define RIGHT_WHEEL_POS 2
#define LEFT_WHEEL_POS 3

#define Vbase 34 //(max/2)

//The PID controller
typedef struct{
    float kp;
    float ki;
    float kd;
    float integrator;
    float previous_error;
    float integrator_limit;
    float frequency;
    float output_limit;
} pid_ctrl;

extern pid_ctrl pid[4];

void PID_init(int i, float kp, float ki, float kd, float Imax, float omax);
float PID_process(int i, float error);

void motorDriveLeft(int drive_level);
void motorDriveRight(int drive_level);

long get_velocity_right_cps(long positionRIGHT);
long get_velocity_left_cps(long positionLEFT);

void mainControl();

#endif	

