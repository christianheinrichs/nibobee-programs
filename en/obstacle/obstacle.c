#include <nibobee/iodefs.h>
#include <nibobee/motpwm.h>
#include <nibobee/delay.h>
#include <nibobee/sens.h>

enum {
    MODE_STOP,
    MODE_DRIVE,
    MODE_BACK,
    MODE_STEER_R,
    MODE_STEER_L,
    MODE_AVOID_R,
    MODE_AVOID_L
};

int16_t speed_l;
int16_t speed_r;
uint16_t counter_ms;

uint8_t perform_check(uint8_t mode);

uint8_t do_stop();
uint8_t do_drive();
uint8_t do_back();
uint8_t do_steer_r();
uint8_t do_steer_l();
uint8_t do_avoid_r();
uint8_t do_avoid_l();

int main() {
    motpwm_init();
    sens_init();
    uint8_t mode;

    while (1 == 1) {
        enable_interrupts();
        delay(1);
        mode = perform_check(mode);

        switch (mode) {
            case MODE_STOP:    mode = do_stop(); break;
            case MODE_DRIVE:   mode = do_drive(); break;
            case MODE_BACK:    mode = do_back(); break;
            case MODE_STEER_R: mode = do_steer_r(); break;
            case MODE_STEER_L: mode = do_steer_l(); break;
            case MODE_AVOID_R: mode = do_avoid_r(); break;
            case MODE_AVOID_L: mode = do_avoid_l(); break;
        }

        switch (mode) {
            case MODE_STOP:     speed_l =    0; speed_r =    0; break;
            case MODE_DRIVE:    speed_l =  600; speed_r =  600; break;
            case MODE_BACK:     speed_l = -500; speed_r = -500; break;
            case MODE_STEER_R:  speed_l =  600; speed_r =  400; break;
            case MODE_STEER_L:  speed_l =  400; speed_l =  600; break;
            case MODE_AVOID_R:  speed_l = -400; speed_r = -600; break;
            case MODE_AVOID_L:  speed_l = -600; speed_r = -400; break;
        }

        motpwm_setLeft(speed_l);
        motpwm_setRight(speed_r);
    }
    return 0;
}

uint8_t perform_check(uint8_t mode) {
    if (sens_getLeft() && sens_getRight()) {
        if (sens_getLeft() == -1 && sens_getRight() == -1) {
            mode = MODE_BACK;
        } else {
            mode = MODE_STOP;
        }
    }
    return mode;
}

uint8_t do_stop() {
    if (sens_getLeft() == 0 && sens_getRight() == 0) {
        return MODE_DRIVE;
    }
    return MODE_STOP;
}

uint8_t do_back() {
    if (sens_getLeft() == 0) {
        return MODE_AVOID_L;
    }
    if (sens_getRight() == 0) {
        return MODE_AVOID_R;
    }
    return MODE_BACK;
}

uint8_t do_drive() {
    if (sens_getRight() == 1) {
        return MODE_STEER_L;
    }
    if (sens_getLeft() == 1) {
        return MODE_STEER_R;
    }
    if (sens_getRight() == -1) {
        return MODE_AVOID_L;
    }
    if (sens_getLeft() == -1) {
        return MODE_AVOID_R;
    }
    return MODE_DRIVE;
}

uint8_t do_steer_r() {
    if (sens_getLeft() == 0) {
        return MODE_DRIVE;
    }
    return MODE_STEER_R;
}

uint8_t do_steer_l() {
    if (sens_getRight() == 0) {
        return MODE_DRIVE;
    }
    return MODE_STEER_L;
}

uint8_t do_avoid_r() {
    if (counter_ms == 0) {
        counter_ms = 1000;
    } else {
        counter_ms--;
    }
    if (counter_ms) {
        return MODE_AVOID_R;
    } else {
        return MODE_DRIVE;
    }
}

uint8_t do_avoid_l() {
    if (counter_ms == 0) {
        counter_ms = 1000;
    } else {
        counter_ms--;
    }
    if (counter_ms) {
        return MODE_AVOID_L;
    } else {
        return MODE_DRIVE;
    }
}
