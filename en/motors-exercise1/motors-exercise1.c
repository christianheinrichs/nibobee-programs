#include <nibobee/iodefs.h>
#include <nibobee/sens.h>
#include <nibobee/motpwm.h>

int main() {
    // Initialize motor IO
    motpwm_init();
    // Initialize feeler IO
    sens_init();

    // This while loop is identical with the one of the program "motors.c"
    // However, you can see slightly different speed values
    while (1 == 1) {
        // Enable interrupts for motor functions
        enable_interrupts();
        int16_t speed_l = 0;
        int16_t speed_r = 0;

        // Set left motor speed depending on status of left feeler
        switch (sens_getLeft()) {
            case  1: speed_l =  750; break;
            case  0: speed_l =    0; break;
            case -1: speed_l = -300; break;
        }

        // Set right motor speed depending on status of right feeler
        switch (sens_getRight()) {
            case  1: speed_r =  750; break;
            case  0: speed_r =    0; break;
            case -1: speed_r = -300; break;
        }

        // Apply the values to the motors
        motpwm_setLeft(speed_l);
        motpwm_setRight(speed_r);
    }
    return 0;
}
