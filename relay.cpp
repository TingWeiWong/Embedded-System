#include "mbed.h"
 
DigitalOut relay(D6);
int on = 1,off = 0;
int main()
{
 
    // Loop forever, relay on/ off for 1 second each
    // LED on relay will blink on / off 
    while(1) {
        relay = on;
        wait(1);
        relay = off;
        wait(1);
    }
}