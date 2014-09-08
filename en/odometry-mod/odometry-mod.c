#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/sens.h>
#include <nibobee/odometry.h>

int main() {
    // Initialize feeler IO, LED IO and odometry sensor IO
    led_init();
    odometry_init();
    sens_init();

    while (1 == 1) {
        // Enable interrupts for odometry sensors
        enable_interrupts();

        // Reset the odometry values on one side,
        // if the corresponding feeler is being interacted with
        if (sens_getLeft()) {
            odometry_getLeft(1);
        } else if (sens_getRight()) {
            odometry_getRight(1);
        }

        // Show the odometry status by turning the wheels
        // either forwards or backwards
        led_set(LED_L_YE, odometry_getLeft(0) > 10);
        led_set(LED_L_RD, odometry_getLeft(0) > 20);
        led_set(LED_R_RD, odometry_getRight(0) > 20);
        led_set(LED_R_YE, odometry_getRight(0) > 10);
    }
    return 0;
}
