#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

int main() {
    led_init();

    while (1 == 1) {
        led_set(1, 1);
        delay(400);
        led_set(1, 0);
        delay(400);
    }
    return 0;
}
