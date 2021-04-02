#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/sens.h>
#include <nibobee/odometry.h>

int main() {
    // Fühler IO, LED IO und Odometriesensor IO initialisieren
    led_init();
    odometry_init();
    sens_init();

    while (1 == 1) {
        // Interrupts für Odometriesensoren aktivieren
        enable_interrupts();

        // Die Odometriewerte auf einer Seite zurücksetzen, wenn der
        // dazugehörige Fühler betätigt wurde
        if (sens_getLeft()) {
            odometry_getLeft(1);
        } else if (sens_getRight()) {
            odometry_getRight(1);
        }

        // Odometriewerte durch Drehen der Räder (sei es vorwärts oder
        // rückwärts) anzeigen
        led_set(LED_L_YE, odometry_getLeft(0) > 10);
        led_set(LED_L_RD, odometry_getLeft(0) > 20);
        led_set(LED_R_RD, odometry_getRight(0) > 20);
        led_set(LED_R_YE, odometry_getRight(0) > 10);
    }
    return 0;
}
