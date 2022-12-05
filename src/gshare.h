#ifndef GSHARE_H
#define GSHARE_H

#include <stdint.h>
#include <stdlib.h>


void initGshare();

uint8_t makePredictionGshare(uint32_t pc);

void trainPredictorGshare(uint32_t pc, uint8_t outcome);

void finishGshare();

#endif