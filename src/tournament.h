#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <stdint.h>
#include <stdlib.h>


void initTournament();

uint8_t makePredictionTournament(uint32_t pc);

void trainPredictorTournament(uint32_t pc, uint8_t outcome);

void finishTournament();

#endif