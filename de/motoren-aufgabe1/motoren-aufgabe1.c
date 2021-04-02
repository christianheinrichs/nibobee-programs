#include <nibobee/iodefs.h>
#include <nibobee/sens.h>
#include <nibobee/motpwm.h>

int main() {
    // Motor IO initialisieren
    motpwm_init();

    // Fühler IO initialisieren
    sens_init();

    // Diese while-Schleife ist identisch mit der aus dem Programm „motoren.c“
    // Jedoch kann man leicht veränderte Geschwindigkeitswerte feststellen
    while (1 == 1) {
        // Interrupts für Motor-Funktionen aktivieren
        enable_interrupts();
        int16_t speed_l = 0;
        int16_t speed_r = 0;

        // Linke Motorgeschwindigkeit abhängig vom Status des linken Fühlers
        // setzen
        switch (sens_getLeft()) {
            case  1: speed_l =  750; break;
            case  0: speed_l =    0; break;
            case -1: speed_l = -300; break;
        }

        // Rechte Motorgeschwindigkeit abhängig vom Status des rechten Fühlers
        // setzen
        switch (sens_getRight()) {
            case  1: speed_r =  750; break;
            case  0: speed_r =    0; break;
            case -1: speed_r = -300; break;
        }

        // PWM-Werte für die Motoren setzen
        motpwm_setLeft(speed_l);
        motpwm_setRight(speed_r);
    }
    return 0;
}
