#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdlib.h>

// 2-bit FSM
#define OUTPUT_ZERO 0
#define OUTPUT_ONE 1

#define ACTION_ZERO OUTPUT_ZERO
#define ACTION_ONE OUTPUT_ONE

#define STATE_ZERO 0
#define STATE_ONE 1
#define STATE_TWO 2
#define STATE_THREE 3


void updateTwoBitsFsmState(uint8_t *curr_state, uint8_t action);

uint8_t getTwoBitsFsmOutput(uint8_t curr_state);

uint32_t getNBitsMask(uint8_t n);

void updateBhr(uint32_t *bhr, uint8_t outcome);

#endif