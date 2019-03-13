# tum-lab-micromouse
Building a robot mouse from scratch - WS 18/19

# Adam's Notes from old repository (in form of diary)
3/1/2019 Problem with velocity sign and Solution: There exists a line of communication between the MCU and the motor. It goes like MCU --> H-bridge --> motor and the other way motor encoder --> MCU decoder. In order to use the convention of forward and backward rotation of the motor as presented in its datasheet and as is supposed to be interpreted by the MCU (in its own datasheet), we have to be sure that the convention holds throuhgout the entire line described. All in all, hardware convention: When rotating forward (clock-wise), alway channel A precedes channel B. This holds in both the motor encoding the info and in the MCU decoding it. Software convention: In the function motorDrive, we need to be careful about the direction we set with dirA and dirB pins of the H-bridge. They have to be set in such a way, that indeed the forward movement of the motor is clock-wise. And they are like that indeed.

Problem of change direction transitions: The idea is to implement a short delay in the driving of the motor, every time we tell it to change directions. This would ensure that the motor transitions are smooth when changing directions. However, we decided not to implement it, since this won't happen that often. Also, we prefer to have full control of the motor instead of sucrificing its control even for few milliseconds for the sake of smooth transitions.

How to calculate the velocity: In the code we just calculate in the timer interrupt (every 10msec), how much the rotation of the shaft of the motor has changed (Dr). To get the real velocity of the wheel spinning, we have to perform some computations. But, since the computations are always fixed (constant), we avoid doing this in the code and compute it by hand instead. The plan is to create something like a look-up table, in order to be able to know right away, what velocity we are driving our motor with, using the 0 - 100% convention of the pwm. From Alex, we have:

Vw(n) = Vcps(n) * wbase /(kE * Gr),

in our case,

Vcps = Dr/10msec, wbase = 2pi/16, kE = 4, Gr = 33 (check the document for explanations). And all this leads to Vw = 0.3 * Dr (rps). If we want the velocity in meters per second, we just need to multiply that with the radius of the wheel.
