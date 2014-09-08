#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

int main() {
    // LED IO initialisieren
    led_init();
    // LED0-LED3 an- und ausschalten mithilfe einer for-Schleife.
    // Dieses Mal jedoch, wechsle die Geschwindigkeit
    while (1 == 1) {
        int time;
        for (time = 50; time < 800; time *= 2) {
            int ledNr;
            for (ledNr = 0; ledNr < 4; ledNr++) {
                led_set(ledNr, 1);
                delay(time);
                led_set(ledNr, 0);
                delay(time);
            }
        }
    }
    return 0;
}
