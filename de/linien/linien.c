#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/line.h>

int main() {
    // LED IO initialisieren
    led_init();

    // Linien-IO initialisieren
    line_init();

    // Die Werte der Liniensensoren anzeigen
    // Ebenfalls anzeigen, ob die Werte zu hoch oder zu niedrig sind
    while (1 == 1) {
        enable_interrupts();
        led_set(LED_L_YE, line_get(LINE_L) > 160);
        led_set(LED_L_RD, line_get(LINE_L) > 240);
        led_set(LED_R_YE, line_get(LINE_R) > 160);
        led_set(LED_R_RD, line_get(LINE_R) > 240);
    }
    return 0;
}
