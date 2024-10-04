/*
 * output_LED7SEG.h
 *
 *  Created on: Oct 4, 2024
 *      Author: DELL
 */

#ifndef INC_OUTPUT_LED7SEG_H_
#define INC_OUTPUT_LED7SEG_H_

#include "main.h"
#include "software_timer.h"

#define LED7SEG_SCANNING_DURATION 10
#define LED7SEG_NUMBER 5

extern int firstSEG;
extern int secondSEG;
extern int mode;

void led7SegInit(void);
void led7Scanning(void);

#endif /* INC_OUTPUT_LED7SEG_H_ */
