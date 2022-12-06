#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdlib.h>


void updateTwoBitsFsmState(uint8_t *curr_state, uint8_t action);

uint8_t getTwoBitsFsmOutput(uint8_t curr_state);

uint32_t getNBitsMask(uint8_t n);

void updateBhr(uint32_t *bhr, uint8_t outcome);

#endif