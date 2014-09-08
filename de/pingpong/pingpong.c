#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/sens.h>
#include <nibobee/delay.h>

enum {
    STATE_IDLE = 0,
    STATE_PULL0 = 1,
    STATE_PULL1 = 2,
    STATE_KICK = 3,
    STATE_PUSH = 4
};

uint8_t calculate_state(uint8_t state, int8_t sensor) {
    switch (state) {
        case STATE_PUSH:
        case STATE_IDLE:
            if (sensor == -1) {
                return STATE_PULL0;
            } else if (sensor == +1) {
                return STATE_PUSH;
            }
            return STATE_IDLE;

        case STATE_PULL0:
            if (sensor == -1) {
                return STATE_PULL1;
            } else if (sensor == +1) {
                return STATE_PUSH;
            }
            return STATE_IDLE;

        case STATE_PULL1:
            if (sensor == -1) {
                return STATE_PULL1;
            }
            return STATE_KICK;

        case STATE_KICK:
            return STATE_IDLE;
    }
    return state;
}

int main() {
    led_init();
    sens_init();

    uint8_t ball_pos = 3;
    int8_t direction = -1;

    uint8_t state_l = STATE_IDLE;
    uint8_t state_r = STATE_IDLE;

    while (1 == 1) {
        delay(100);

        state_l = calculate_state(state_l, sens_getLeft());
        if( ((state_l == STATE_PUSH) && (ball_pos == 1)) ||
            ((state_l == STATE_KICK) && (ball_pos == 0)) ) {
            direction = +1;
        }

        state_r = calculate_state(state_r, sens_getRight());
        if( ((state_r == STATE_PUSH) && (ball_pos == 2)) ||
            ((state_r == STATE_KICK) && (ball_pos == 3)) ) {
            direction = -1;
        }

        if (direction == +1) {
            if (ball_pos < 3) {
                ball_pos++;
            } else {
                direction = 0;
            }
        }

        if (direction == -1) {
            if (ball_pos > 0) {
                ball_pos--;
            } else {
                direction = 0;
            }
        }

        led_set(LED_L_YE, ball_pos == 0);
        led_set(LED_L_RD, ball_pos == 1);
        led_set(LED_R_RD, ball_pos == 2);
        led_set(LED_R_YE, ball_pos == 3);
    }
    return 0;
}
