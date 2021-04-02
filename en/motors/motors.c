#include <nibobee/iodefs.h>
#include <nibobee/sens.h>
#include <nibobee/motpwm.h>

int main() {
    // Initialise motor IO
    motpwm_init();
    // Initialise feeler IO
    sens_init();

    while (1 == 1) {
        // Enable interrupts for motor functions
        enable_interrupts();
        int16_t speed_l = 0;
        int16_t speed_r = 0;

        // Set left motor speed depending on status of left feeler
        switch (sens_getLeft()) {
            case  1: speed_l =  500; break;
            case  0: speed_l =    0; break;
            case -1: speed_l = -500; break;
        }

        // Set right motor speed depending on status of right feeler
        switch (sens_getRight()) {
            case  1: speed_r =  500; break;
            case  0: speed_r =    0; break;
            case -1: speed_r = -500; break;
        }

        // Set motor PWM values
        motpwm_setLeft(speed_l);
        motpwm_setRight(speed_r);
    }
    return 0;
}
