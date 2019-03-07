#ifndef STATE_H
#define STATE_H

//Enum of the different possible states
typedef enum {
    IDLE,
    GO_STRAIGHT,
    TURN_LEFT,
    TURN_RIGHT
} States;

//Struct containing the sensor measurements (discrete))
struct Observation {
   int front_free;
   int left_free;
   int right_free;
};


void initState( );

void triggerAction();

void updateState( struct Observation );

#endif /* STATE_H */