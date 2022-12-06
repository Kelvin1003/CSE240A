#include "custom.h"

#include <string.h>

#include "predictor.h"
#include "utils.h"


static uint32_t *lhr;
static uint32_t lhr_mask;
static uint8_t *lht;
static uint32_t lht_mask;

static uint32_t ghr;
static uint8_t *nottaken_ght;
static uint8_t *taken_ght;
static uint32_t ght_mask;
static uint8_t *ght_chooser;
static uint32_t ght_chooser_mask;

static uint8_t *pre_chooser;


void initCustom() {
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
    nottaken_ght = (uint8_t*) malloc(ght_size);
    taken_ght = (uint8_t*) malloc(ght_size);
    memset(nottaken_ght, WN, ght_size);
    memset(taken_ght, WT, ght_size);
    ght_mask = getNBitsMask(ghistoryBits);

    size_t ght_chooser_size = sizeof(uint8_t) * (1u << ghtChooserBits);
    ght_chooser = (uint8_t*) malloc(ght_chooser_size);
    memset(ght_chooser, WNG, ght_chooser_size);
    ght_chooser_mask = getNBitsMask(ghtChooserBits);

    size_t pre_chooser_size = sizeof(uint8_t) * (1u << ghistoryBits);
    pre_chooser = (uint8_t*) malloc(pre_chooser_size);
    memset(pre_chooser, WG, pre_chooser_size);
}


uint8_t makePredictionCustom(uint32_t pc) {
    uint32_t ght_index = (ghr ^ pc) & ght_mask;

    if (getTwoBitsFsmOutput(pre_chooser[ght_index]) == LOCAL_PRE) {
        uint32_t lhr_index = pc & lhr_mask;
        uint32_t lht_index = lhr[lhr_index] & lht_mask;
        return getTwoBitsFsmOutput(lht[lht_index]);
    }
    else {
        uint32_t ght_choose_index = pc & ght_chooser_mask;
        if (getTwoBitsFsmOutput(ght_chooser[ght_choose_index]) == NOTTAKEN_GHT) {
            return getTwoBitsFsmOutput(nottaken_ght[ght_index]); 
        }
        else {
            return getTwoBitsFsmOutput(taken_ght[ght_index]); 
        }
    }
}


void trainPredictorCustom(uint32_t pc, uint8_t outcome) {
    uint32_t lhr_index = pc & lhr_mask;
    uint32_t lht_index = lhr[lhr_index] & lht_mask;
    uint8_t lht_predict = getTwoBitsFsmOutput(lht[lht_index]);
    // Update LHT
    updateTwoBitsFsmState(lht + lht_index, outcome);
    uint32_t ght_index = (ghr ^ pc) & ght_mask;        
    uint32_t ght_choose_index = pc & ght_chooser_mask;
    uint8_t ght_predict;
    // Update GHT
    if (getTwoBitsFsmOutput(ght_chooser[ght_choose_index]) == NOTTAKEN_GHT) {
        ght_predict = getTwoBitsFsmOutput(nottaken_ght[ght_index]); 
        updateTwoBitsFsmState(nottaken_ght + ght_index, outcome);
        // Update GHT chooser
        if (!(ght_predict == outcome && ght_predict == TAKEN)) {
            updateTwoBitsFsmState(ght_chooser + ght_choose_index, outcome);
        }
    }
    else {
        ght_predict = getTwoBitsFsmOutput(taken_ght[ght_index]); 
        updateTwoBitsFsmState(taken_ght + ght_index, outcome);
        // Update GHT chooser
        if (!(ght_predict == outcome && ght_predict == NOTTAKEN)) {
            updateTwoBitsFsmState(ght_chooser + ght_choose_index, outcome);
        }
    }

    // Update predictor chooser
    if (lht_predict == outcome && ght_predict != outcome) {
        updateTwoBitsFsmState(pre_chooser + ght_index, LOCAL_PRE);
    }
    else if (lht_predict != outcome && ght_predict == outcome) {
        updateTwoBitsFsmState(pre_chooser + ght_index, GLOBAL_PRE);
    }

    // Update BHR
    updateBhr(lhr + lhr_index, outcome);
    updateBhr(&ghr, outcome);
}


void finishCustom() {
    free(lhr);
    free(lht);
    free(nottaken_ght);
    free(taken_ght);
    free(ght_chooser);
    free(pre_chooser);
}