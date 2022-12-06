#include "utils.h"


void updateTwoBitsFsmState(uint8_t *curr_state, uint8_t action) {
    if (action == ACTION_ONE) {
        if (*curr_state != STATE_THREE) ++ *curr_state;
    }
    else {
        if (*curr_state != STATE_ZERO) -- *curr_state;
    }
}


uint8_t getTwoBitsFsmOutput(uint8_t curr_state) {
    return (curr_state >= STATE_TWO) ? OUTPUT_ONE : OUTPUT_ZERO;
}


uint32_t getNBitsMask(uint8_t n) {
    return (1 << n) - 1;
}


void updateBhr(uint32_t *bhr, uint8_t outcome) {
    *bhr = (*bhr << 1) + outcome;
}