#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

int main() {
    led_init();
    while (1 == 1) {
        int ledNr;

        for (ledNr = 0; ledNr < 4; ledNr++) {
            led_set(ledNr, 1);
            delay(300);
        }
        for (ledNr = 3; ledNr > -1; ledNr--) {
            led_set(ledNr, 0);
            delay(300);
        }
    }
    return 0;
}
