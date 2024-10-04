/*
 * fsm_processing.h
 *
 *  Created on: Oct 4, 2024
 *      Author: DELL
 */

#ifndef INC_FSM_PROCESSING_H_
#define INC_FSM_PROCESSING_H_

#include "software_timer.h"
#include "output_LED7SEG.h"
#include "output_traffic.h"
#include "input_reading.h"

enum FSM_STATE {FSM_NORMAL, FSM_RED_MOD, FSM_AMBER_MOD, FSM_GREEN_MOD};

void fsmInit(void);
void fsmReInit(enum FSM_STATE state);
void fsmProcessing(void);

#endif /* INC_FSM_PROCESSING_H_ */
