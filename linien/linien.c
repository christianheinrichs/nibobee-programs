#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/line.h>

int main() {
    led_init();
    line_init();

    while (1 == 1) {
        enable_interrupts();
        led_set(LED_L_YE, line_get(LINE_L) > 160);
        led_set(LED_L_RD, line_get(LINE_L) > 240);
        led_set(LED_R_YE, line_get(LINE_R) > 160);
        led_set(LED_R_RD, line_get(LINE_R) > 240);
    }
    return 0;
}
