/*
 * File:   stateFunctions.c
 * Author: frankzl
 *
 * Created on February 28, 2019, 1:16 PM
 */


#include "stateFunctions.h"

//The state variable
static States state;

//Initiallize state
void initState(){
    state = IDLE;
}

//Update state depending on sensor measurements, to take discrete decisions. 
//To do: Set the thresholds of what is free and what not.
//To do: Only use the right sensor to take decisions and jump to appropriate state.
void updateState(struct Observation obs){
    if (obs.right_free){
        state = TURN_RIGHT;
    }else if (obs.front_free){
        state = GO_STRAIGHT;
    }else {
        state = TURN_LEFT;
    }
}

//Take action according to the state we are in, use controller.
//The idle and straight states are rather straight-forward
//The turn right and left will use a type of fuzzy description: "Turn right hard when no wall detected",
// "Turn left hard when right wall too close", etc.
void triggerAction(){
    switch(state){
        case IDLE:
            // TODO
            break;
        case TURN_RIGHT:
            // TODO
            break;
        case TURN_LEFT:
            // TODO
            break;
        case GO_STRAIGHT:
            // TODO
            break;
    }
}