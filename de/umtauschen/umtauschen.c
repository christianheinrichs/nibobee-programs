#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

int main() {
    led_init();
    while (1 == 1) {
        int ledNr;
        for (ledNr = 0; ledNr < 4; ledNr++) {
            int time;
            for (time = 800; time > 50; time /= 2) {
                led_set(ledNr, 1);
                delay(time);
                led_set(ledNr, 0);
                delay(time);
            }
        }
    }
    return 0;
}
