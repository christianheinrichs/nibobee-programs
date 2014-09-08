#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/sens.h>

int main() {
    led_init(); // Initialize LED IO
    sens_init(); // Initialize odometry sensor IO

    while (1 == 1) {
        int8_t status_L = sens_getLeft();

        // Turn left LEDs on or off, depending on the status of the left feeler
        switch (status_L) {
            case -1: led_set(LED_L_RD, 0); led_set(LED_L_YE, 1);
            break;
            case +1: led_set(LED_L_RD, 1); led_set(LED_L_YE, 0);
            break;
            default: led_set(LED_L_RD, 0); led_set(LED_L_YE, 0);
            break;
        }

        int8_t status_R = sens_getRight();

        // Turn right LEDs on or off, depending on the status of the right feeler
        switch (status_R) {
            case -1: led_set(LED_R_RD, 0); led_set(LED_R_YE, 1);
            break;
            case +1: led_set(LED_R_RD, 1); led_set(LED_R_YE, 0);
            break;
            default: led_set(LED_R_RD, 0); led_set(LED_R_YE, 0);
            break;
        }
    }
    return 0;
}
