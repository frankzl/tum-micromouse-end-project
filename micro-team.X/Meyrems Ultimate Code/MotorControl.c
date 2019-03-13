#include "xc.h"
#include "MotorControl.h"  
#include "PWMSetup.h"
#include "IOSetup.h"

pid_ctrl pid[4];

//Initialize PID
void PID_init(int i, float kp, float ki, float kd, float Imax, float Omax)
{   
    pid[i].kp = kp;
    pid[i].ki = ki;
    pid[i].kd = kd;
    pid[i].integrator = 0.;
    pid[i].previous_error = 0.;
    pid[i].integrator_limit = Imax;
    pid[i].frequency = 1.;
    pid[i].output_limit = Omax;
}

//Main control function
float PID_process(int i, float error)
{
    float output;
    pid[i].integrator += error;
    
    if (pid[i].integrator > pid[i].integrator_limit){
        pid[i].integrator = pid[i].integrator_limit;
    } else if (pid[i].integrator < -pid[i].integrator_limit){
        pid[i].integrator = - pid[i].integrator_limit;
    }
    
    output =   - pid[i].kp * error;
    output +=  - pid[i].ki * pid[i].integrator / pid[i].frequency;
    output +=  - pid[i].kd * (error - pid[i].previous_error) * pid[i].frequency;
    
    if (output> pid[i].output_limit) output=pid[i].output_limit;
    if (output< -pid[i].output_limit) output=- pid[i].output_limit;
    
    pid[i].previous_error = error;
    return output;
}

void motorDriveLeft(int drive_level)
{
    //sanity check for drive_level
    if (drive_level > 100) drive_level = 100;
    if (drive_level < -100) drive_level = -100;
    
    //set driving direction to h-bridge and speed (duty cycle proportion) to PWM
    if (drive_level >= 0)
    {
        DIR_A_LEFT = 1;
        DIR_B_LEFT = 0;
        setLEFTDC(drive_level);
    }
    
    else
    {
        DIR_A_LEFT = 0;
        DIR_B_LEFT = 1;
        setLEFTDC(-drive_level);
    }   
}


void motorDriveRight(int drive_level)
{
    //sanity check for drive_level
    if (drive_level > 100) drive_level = 100;
    if (drive_level < -100) drive_level = -100;
    
    //set driving direction to h-bridge and speed (duty cycle proportion) to PWM
    if (drive_level >= 0)
    {
        DIR_A_RIGHT = 1;
        DIR_B_RIGHT = 0;
        setRIGHTDC(drive_level);
    }
    
    else
    {
        DIR_A_RIGHT = 0;
        DIR_B_RIGHT = 1;
        setRIGHTDC(-drive_level);
    }
}

long get_velocity_right_cps(long positionRIGHT)
{    
    static long old_position = 0x7fff;
    long velocity_cps;
    long current_position;
   
    current_position = positionRIGHT + POS2CNT;
    velocity_cps = current_position - old_position;
    old_position = current_position;
    
    return velocity_cps;
}

long get_velocity_left_cps(long positionLEFT)
{
    static long old_position = 0x7fff;
    long velocity_cps;
    long current_position;

    current_position = positionLEFT + POS1CNT;
    velocity_cps = current_position - old_position;
    old_position = current_position;

    return velocity_cps;
}

void mainControl()
{    
    float distance_LEFT;
    float distance_RIGHT;
    float veloRIGHT;
    float veloLEFT;
    
    float Vbase_RIGHT = Vbase + PID_process(2, distance_LEFT-distance_RIGHT); 
    float Vbase_LEFT = Vbase - PID_process(3, distance_LEFT-distance_RIGHT);
    
    veloRIGHT = get_velocity_right_cps(positionRIGHT);
    veloLEFT = get_velocity_left_cps(positionLEFT);
    
    int PDC_RIGHT = (int)PID_process(0, Vbase_RIGHT-veloRIGHT);
    int PDC_LEFT = (int)PID_process(1, Vbase_LEFT-veloLEFT);
    
    motorDriveRight(PDC_RIGHT);
    motorDriveLeft(PDC_LEFT);
}
