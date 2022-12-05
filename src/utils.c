#include "utils.h"

#include "predictor.h"


void twoBitsFsm(uint8_t *curr_state, uint8_t outcome) {
    if (outcome == TAKEN) {
        if (*curr_state != ST) ++ *curr_state;
    }
    else {
        if (*curr_state != SN) -- *curr_state;
    }
}