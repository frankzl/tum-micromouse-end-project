/*
 * File:   stateFunctions.c
 * Author: frankzl
 *
 * Created on February 28, 2019, 1:16 PM
 */


#include "stateFunctions.h"


static States state;

void initState(){
    state = IDLE;
}

void updateState(struct Observation obs){
    if (obs.right_free){
        state = TURN_RIGHT;
    }else if (obs.front_free){
        state = GO_STRAIGHT;
    }else {
        state = TURN_LEFT;
    }
}

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