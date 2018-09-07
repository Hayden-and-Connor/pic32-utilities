#include <p32xxxx.h>
#include <inttypes.h>

#ifndef GPIO_H
#define GPIO_H

#define HIGH 1
#define LOW 0
 
#define INPUT 1
#define OUTPUT 0

void initPin(int pin, int value);
void writePin(int pin, int value);

int readPin(int pin);
int getPinMode(int pin);

void clearPins();

#endif