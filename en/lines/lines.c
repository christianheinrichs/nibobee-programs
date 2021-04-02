#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/line.h>

int main() {
    // Initialise LED IO
    led_init();

    // Initialise line IO
    line_init();

    // Show the values of the line sensors
    // Also show, if the values are too high or too low
    while (1 == 1) {
        enable_interrupts();
        led_set(LED_L_YE, line_get(LINE_L) > 160);
        led_set(LED_L_RD, line_get(LINE_L) > 240);
        led_set(LED_R_YE, line_get(LINE_R) > 160);
        led_set(LED_R_RD, line_get(LINE_R) > 240);
    }
    return 0;
}
