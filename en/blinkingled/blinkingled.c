#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

int main() {
    // Initialize LED IO
    led_init();

    // Turn LED1 on and off with a delay of 400ms
    while (1 == 1) {
        led_set(1, 1);
        delay(400);
        led_set(1, 0);
        delay(400);
    }
    return 0;
}
