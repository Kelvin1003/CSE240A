#ifndef CUSTOM_H
#define CUSTOM_H

#include <stdint.h>
#include <stdlib.h>


void initCustom();

uint8_t makePredictionCustom(uint32_t pc);

void trainPredictorCustom(uint32_t pc, uint8_t outcome);

void finishCustom();

#endif