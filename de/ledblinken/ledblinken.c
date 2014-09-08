#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

int main() {
    // LED IO initialisieren
    led_init();

    // LED1 an- und ausschalten mit einer Verzögerung von 400ms
    while (1 == 1) {
        led_set(1, 1);
        delay(400);
        led_set(1, 0);
        delay(400);
    }
    return 0;
}
