#include <nibobee/iodefs.h>
#include <nibobee/sens.h>
#include <nibobee/motpwm.h>

int main() {
    motpwm_init();
    sens_init();

    while (1 == 1) {
        enable_interrupts();
        int16_t speed_l = 0;
        int16_t speed_r = 0;

        switch (sens_getLeft()) {
            case  1: speed_l =  500; break;
            case  0: speed_l =    0; break;
            case -1: speed_l = -500; break;
        }

        switch (sens_getRight()) {
            case  1: speed_r =  500; break;
            case  0: speed_r =    0; break;
            case -1: speed_r = -500; break;
        }

        motpwm_setLeft(speed_l);
        motpwm_setRight(speed_r);
    }
    return 0;
}
