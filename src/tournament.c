#include "tournament.h"

#include <string.h>

#include "predictor.h"
#include "utils.h"


static uint32_t *lhr;
static uint32_t lhr_mask;
static uint8_t *lht;
static uint32_t lht_mask;

static uint32_t ghr;
static uint8_t *ght;
static uint32_t ght_mask;

static uint8_t *chooser;


void initTournament() {
    size_t lhr_size = sizeof(uint32_t) * (1u << pcIndexBits);
    lhr = (uint32_t*) malloc(lhr_size);
    memset(lhr, 0, lhr_size);
    lhr_mask = getNBitsMask(pcIndexBits);
    size_t lht_size = sizeof(uint8_t) * (1u << lhistoryBits);
    lht = (uint8_t*) malloc(lht_size);
    memset(lht, WN, lht_size);
    lht_mask = getNBitsMask(lhistoryBits);

    ghr = 0;
    size_t ght_size = sizeof(uint8_t) * (1u << ghistoryBits);
    ght = (uint8_t*) malloc(ght_size);
    memset(ght, WN, ght_size);
    ght_mask = getNBitsMask(ghistoryBits);

    size_t chooser_size = sizeof(uint8_t) * (1u << ghistoryBits);
    chooser = (uint8_t*) malloc(chooser_size);
    memset(chooser, WG, chooser_size);
}


uint8_t makePredictionTournament(uint32_t pc) {
    uint32_t ght_index = ghr & ght_mask;

    if (getTwoBitsFsmOutput(chooser[ght_index]) == LOCAL_PRE) {
        uint32_t lhr_index = pc & lhr_mask;
        uint32_t lht_index = lhr[lhr_index] & lht_mask;
        return getTwoBitsFsmOutput(lht[lht_index]);
    }
    else {
        return getTwoBitsFsmOutput(ght[ght_index]); 
    }
}


void trainPredictorTournament(uint32_t pc, uint8_t outcome) {
    uint32_t lhr_index = pc & lhr_mask;
    uint32_t lht_index = lhr[lhr_index] & lht_mask;
    uint8_t lht_predict = getTwoBitsFsmOutput(lht[lht_index]);
    uint32_t ght_index = ghr & ght_mask;
    uint8_t ght_predict = getTwoBitsFsmOutput(ght[lht_index]);

    if (lht_predict == outcome && ght_predict != outcome) {
        updateTwoBitsFsmState(chooser + ght_index, LOCAL_PRE);
    }
    else if (lht_predict != outcome && ght_predict == outcome) {
        updateTwoBitsFsmState(chooser + ght_index, GLOBAL_PRE);
    }

    updateTwoBitsFsmState(lht + lht_index, outcome);
    updateTwoBitsFsmState(ght + ght_index, outcome);

    updateBhr(lhr + lhr_index, outcome);
    updateBhr(&ghr, outcome);
}


void finishTournament() {
    free(lhr);
    free(lht);
    free(ght);
    free(chooser);
}