#include "gpio.h"

#define PORTSIZE 5

static int PORTA_STATE;
static int PORTB_STATE;

static int TRISA_STATE;
static int TRISB_STATE;

// initialize a pin as either an input or output
void initPin(int pin, int value) {
	// figure out which port is driving the pin we want
    int *port = (pin < PORTSIZE) ? &TRISA_STATE : &TRISB_STATE;

    if(pin >= PORTSIZE) pin -= (PORTSIZE);

    // update state to reflect new value
    if(value)   *port |=  (1 << (pin));
    else        *port &= ~(1 << (pin));

    // update registers to match our new state
    TRISA = TRISA_STATE;
    TRISB = TRISB_STATE;
}

void writePin(int pin, int value) {
	// figure out which port is driving the pin we want
    int *port = (pin < PORTSIZE) ? &PORTA_STATE : &PORTB_STATE;

    if(pin >= PORTSIZE) pin -= (PORTSIZE);

    // update state to reflect new value
    if(value)   *port |=  (1 << (pin));
    else        *port &= ~(1 << (pin));

    // update registers to match our new state
    PORTA = PORTA_STATE;
    PORTB = PORTB_STATE;
}  

int readPin(int pin) {
    int* tris = (pin < PORTSIZE) ? &TRISA_STATE : &TRISB_STATE;
    
    // if the pin is an input
    if(*tris & (1 << pin)) {
        return ((pin < PORTSIZE ? PORTA : PORTB) & (1 << pin)) >> pin;
    } else {
        int* port = (pin < PORTSIZE) ? &PORTA_STATE : &PORTB_STATE;
        return (*port & (1 << pin)) >> pin;
    }
}

int getPinState(int pin){
    int* tris = (pin < PORTSIZE) ? &TRISA_STATE : &TRISB_STATE;
    
    // if the pin is an input
    if(*tris & (1 << pin)){
        return 1;
    } else {
        return 0;
    }
}


//set all pins to 0
void clearPins() {
    PORTA_STATE = 0;
    PORTB_STATE = 0;

    // update registers to match our new state
    PORTA = PORTA_STATE;
    PORTB = PORTB_STATE;
}