#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

int main() {
    // Initialize LED IO
    led_init();

    // Turn LED0-LED3 on and off by using a for loop
    while (1 == 1) {
        int ledNr;

        for (ledNr = 0; ledNr < 4; ledNr++) {
            led_set(ledNr, 1);
            delay(350);
            led_set(ledNr, 0);
            delay(150);
        }
    }
    return 0;
}
