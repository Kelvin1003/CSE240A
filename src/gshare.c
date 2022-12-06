#include "gshare.h"

#include <string.h>

#include "predictor.h"
#include "utils.h"


static uint32_t bhr;
static uint8_t *bht;
static uint32_t mask;


void initGshare() {
    bhr = 0;

    size_t buffer_size = sizeof(uint8_t) * (1u << ghistoryBits);
    bht = (uint8_t*) malloc(buffer_size);
    memset(bht, WN, buffer_size);

    mask = getNBitsMask(ghistoryBits);
}


uint8_t makePredictionGshare(uint32_t pc) {
    uint32_t index = (pc ^ bhr) & mask;

    return getTwoBitsFsmOutput(bht[index]);
}


void trainPredictorGshare(uint32_t pc, uint8_t outcome) {
    uint32_t index = (pc ^ bhr) & mask;

    updateTwoBitsFsmState(bht + index, outcome);

    updateBhr(&bhr, outcome);
}


void finishGshare() {
    free(bht);
}