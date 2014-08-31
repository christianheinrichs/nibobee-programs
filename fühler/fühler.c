#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/sens.h>

int main() {
    led_init();  // LED IO initialisieren
    sens_init(); // Odometriesensor IO initialisieren

    while (1 == 1) {
        int8_t status_L = sens_getLeft();

        switch (status_L) {
            case -1: led_set(LED_L_RD, 0); led_set(LED_L_YE, 1);
            break;
            case +1: led_set(LED_L_RD, 1); led_set(LED_L_YE, 0);
            break;
            default: led_set(LED_L_RD, 0); led_set(LED_L_YE, 0);
            break;
        }

        int8_t status_R = sens_getRight();

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
