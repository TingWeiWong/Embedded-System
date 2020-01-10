#include "mbed.h"
#include <iostream>
using namespace std;

// main() runs in its own thread in the OS

// Global variables 


DigitalOut buzzer(D12);

InterruptIn motion(D5);


int motion_detected = 0;
 
void irq_handler(void)
{
    motion_detected = 1;
}


int main()
{
    int cnt = 0;
    motion.rise(&irq_handler);  
    while(1) {
        if(motion_detected) {
            cnt++;
            motion_detected = 0;
            printf("Hello! I've detected %d times since reset\n", cnt);
            for (int i = 0; i < 11; i++) {
                buzzer = i % 2;
                cout << "Buzzer = " << buzzer << endl;
                wait(1);
            }
        }
    }
}
