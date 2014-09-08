#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

int main() {
    led_init();
    while (1 == 1) {
        int ledNr;
        for (ledNr = 0; ledNr < 4; ledNr++) {
            led_set(ledNr, 1);
            delay(50);
            led_set(ledNr, 0);
            delay(50);
        }
        for (ledNr = 2; ledNr > 0; ledNr--) {
            led_set(ledNr, 1);
            delay(50);
            led_set(ledNr, 0);
            delay(50);
        }
    }
    return 0;
}
