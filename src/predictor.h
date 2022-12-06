//========================================================//
//  predictor.h                                           //
//  Header file for the Branch Predictor                  //
//                                                        //
//  Includes function prototypes and global predictor     //
//  variables and defines                                 //
//========================================================//

#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <stdint.h>
#include <stdlib.h>

#include "utils.h"

//
// Student Information
//
extern const char *studentName;
extern const char *studentID;
extern const char *email;

//------------------------------------//
//      Global Predictor Defines      //
//------------------------------------//
#define NOTTAKEN  OUTPUT_ZERO
#define TAKEN     OUTPUT_ONE

// The Different Predictor Types
#define STATIC      0
#define GSHARE      1
#define TOURNAMENT  2
#define CUSTOM      3
extern const char *bpName[];

// Definitions for 2-bit counters
#define SN  STATE_ZERO			// predict NT, strong not taken
#define WN  STATE_ONE			// predict NT, weak not taken
#define WT  STATE_TWO			// predict T, weak taken
#define ST  STATE_THREE			// predict T, strong taken

// Chooser predictor
#define GLOBAL_PRE OUTPUT_ZERO
#define LOCAL_PRE  OUTPUT_ONE

#define SG  STATE_ZERO			// using global predictor, strong
#define WG  STATE_ONE			// using global predictor, weak
#define WL  STATE_TWO			// using local predictor, weak
#define SL  STATE_THREE			// using local predictor, strong

// Chooser ght
#define NOTTAKEN_GHT OUTPUT_ZERO
#define TAKEN_GHT  OUTPUT_ONE

#define SNG  STATE_ZERO			// using nottaken ght, strong
#define WNG  STATE_ONE			// using nottaken ght, weak
#define WTG  STATE_TWO			// using taken ght, weak
#define STG  STATE_THREE		// using taken ght, strong

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//
extern int ghistoryBits; // Number of bits used for Global History
extern int lhistoryBits; // Number of bits used for Local History
extern int pcIndexBits;  // Number of bits used for PC index
extern int ghtChooserBits; // Number of bits used for GHT chooser
extern int bpType;       // Branch Prediction Type
extern int verbose;

//------------------------------------//
//    Predictor Function Prototypes   //
//------------------------------------//

// Initialize the predictor
//
void init_predictor();

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t make_prediction(uint32_t pc);

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void train_predictor(uint32_t pc, uint8_t outcome);


// Free memory
void finish_predictor();

#endif
