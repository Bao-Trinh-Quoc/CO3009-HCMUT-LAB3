/*
 * fsm_processing.c
 *
 *  Created on: Oct 4, 2024
 *      Author: DELL
 */

#include "fsm_processing.h"

enum FSM_STATE fsmState = FSM_NORMAL;

void fsmInit(void)
{
	trafficInit();
	fsmReInit(FSM_NORMAL);
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
}

void fsmReInit(enum FSM_STATE state)
{
	switch (state)
	{
	case FSM_NORMAL:
		setTimer(1, TRAFFIC_SECOND_DURATION);							// For COUNTDOWN
		firstSEG = trafficRedDuration;
		secondSEG = trafficGreenDuration;
		mode = 1;
		trafficReInit(0, TRAFFIC_RED);
		trafficReInit(1, TRAFFIC_GREEN);
		fsmState = FSM_NORMAL;
		break;
	case FSM_RED_MOD:
		setTimer(1, TRAFFIC_BLINKING_DURATION);
		firstSEG = trafficRedDuration;
		secondSEG = trafficRedDuration;
		mode = 2;
		trafficReInit(0, TRAFFIC_OFF);
		trafficReInit(1, TRAFFIC_OFF);
		fsmState = FSM_RED_MOD;
		break;
	case FSM_AMBER_MOD:
		setTimer(1, TRAFFIC_BLINKING_DURATION);
		firstSEG = trafficAmberDuration;
		secondSEG = trafficAmberDuration;
		mode = 3;
		trafficReInit(0, TRAFFIC_OFF);
		trafficReInit(1, TRAFFIC_OFF);
		fsmState = FSM_AMBER_MOD;
		break;
	case FSM_GREEN_MOD:
		setTimer(1, TRAFFIC_BLINKING_DURATION);
		firstSEG = trafficGreenDuration;
		secondSEG = trafficGreenDuration;
		mode = 4;
		trafficReInit(0, TRAFFIC_OFF);
		trafficReInit(1, TRAFFIC_OFF);
		fsmState = FSM_GREEN_MOD;
		break;
	default:
		break;
	}
}

void fsmProcessing(void)
{
	switch (fsmState)
	{
	case FSM_NORMAL:

		if (getTimerFlag(1) == 1)
		{
			setTimer(1, TRAFFIC_SECOND_DURATION);

			switch(trafficState[0])
			{
			case TRAFFIC_RED:
				firstSEG--;
				if (firstSEG <= 0)
				{
					firstSEG = trafficGreenDuration;
					trafficReInit(0, TRAFFIC_GREEN);
				}

				break;
			case TRAFFIC_AMBER:
				firstSEG--;
				if (firstSEG <= 0)
				{
					firstSEG = trafficRedDuration;
					trafficReInit(0, TRAFFIC_RED);
				}

				break;
			case TRAFFIC_GREEN:
				firstSEG--;
				if (firstSEG <= 0)
				{
					firstSEG = trafficAmberDuration;
					trafficReInit(0, TRAFFIC_AMBER);
				}
				break;
			default:
				break;
			}

			switch(trafficState[1])
			{
			case TRAFFIC_RED:
				secondSEG--;
				if (secondSEG <= 0)
				{
					secondSEG = trafficGreenDuration;
					trafficReInit(1, TRAFFIC_GREEN);
				}

				break;
			case TRAFFIC_AMBER:
				secondSEG--;
				if (secondSEG <= 0)
				{
					secondSEG = trafficRedDuration;
					trafficReInit(1, TRAFFIC_RED);
				}
				break;
			case TRAFFIC_GREEN:
				secondSEG--;
				if (secondSEG <= 0)
				{
					secondSEG = trafficAmberDuration;
					trafficReInit(1, TRAFFIC_AMBER);
				}
				break;
			default:
				break;
			}
		}

		if (buttonPressed(0))
		{
			fsmReInit(FSM_RED_MOD);
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
		}
		break;
	case FSM_RED_MOD:
		if (getTimerFlag(1) == 1)
		{
			switch (trafficState[0]) {
				case TRAFFIC_OFF:
					setTimer(1, TRAFFIC_BLINKING_DURATION);
					trafficReInit(0, TRAFFIC_RED);
					trafficReInit(1, TRAFFIC_RED);
					break;
				case TRAFFIC_RED:
					setTimer(1, TRAFFIC_BLINKING_DURATION);
					trafficReInit(0, TRAFFIC_OFF);
					trafficReInit(1, TRAFFIC_OFF);
					break;
				default:
					break;
			}
		}
		if (buttonPressed(0))
		{
			fsmReInit(FSM_AMBER_MOD);
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
		}

		if (buttonPressed(1))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			firstSEG++;
			if (firstSEG > 99)
			{
				firstSEG = 1;
			}
			secondSEG++;
			if (secondSEG > 99)
			{
				secondSEG = 1;
			}
		}

		if (buttonPressed(2))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			firstSEG--;
			if (firstSEG < 1)
			{
				firstSEG = 99;
			}
			secondSEG--;
			if (secondSEG < 1)
			{
				secondSEG = 99;
			}
		}

		if (buttonPressed(3))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);
			trafficRedDuration = firstSEG;
		}
		break;
	case FSM_AMBER_MOD:
		if (getTimerFlag(1) == 1)
		{
			switch (trafficState[0]) {
				case TRAFFIC_OFF:
					setTimer(1, TRAFFIC_BLINKING_DURATION);
					trafficReInit(0, TRAFFIC_AMBER);
					trafficReInit(1, TRAFFIC_AMBER);
					break;
				case TRAFFIC_AMBER:
					setTimer(1, TRAFFIC_BLINKING_DURATION);
					trafficReInit(0, TRAFFIC_OFF);
					trafficReInit(1, TRAFFIC_OFF);
					break;
				default:
					break;
			}
		}
		if (buttonPressed(0))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			fsmReInit(FSM_GREEN_MOD);
		}

		if (buttonPressed(1))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			firstSEG++;
			if (firstSEG > 99)
			{
				firstSEG = 1;
			}
			secondSEG++;
			if (secondSEG > 99)
			{
				secondSEG = 1;
			}
		}

		if (buttonPressed(2))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			firstSEG--;
			if (firstSEG < 1)
			{
				firstSEG = 99;
			}
			secondSEG--;
			if (secondSEG < 1)
			{
				secondSEG = 99;
			}
		}

		if (buttonPressed(3))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);
			trafficAmberDuration = firstSEG;
		}
		break;
	case FSM_GREEN_MOD:
		if (getTimerFlag(1) == 1)
		{
			switch (trafficState[0])
			{
			case TRAFFIC_OFF:
				setTimer(1, TRAFFIC_BLINKING_DURATION);
				trafficReInit(0, TRAFFIC_GREEN);
				trafficReInit(1, TRAFFIC_GREEN);
				break;
			case TRAFFIC_GREEN:
				setTimer(1, TRAFFIC_BLINKING_DURATION);
				trafficReInit(0, TRAFFIC_OFF);
				trafficReInit(1, TRAFFIC_OFF);
				break;
			default:
				break;
			}
		}

		if (buttonPressed(0))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			fsmReInit(FSM_NORMAL);
		}

		if (buttonPressed(1))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			firstSEG++;
			if (firstSEG > 99)
			{
				firstSEG = 1;
			}
			secondSEG++;
			if (secondSEG > 99)
			{
				secondSEG = 1;
			}
		}

		if (buttonPressed(2))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			firstSEG--;
			if (firstSEG < 1)
			{
				firstSEG = 99;
			}
			secondSEG--;
			if (secondSEG < 1)
			{
				secondSEG = 99;
			}
		}

		if (buttonPressed(3))
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);
			trafficGreenDuration = firstSEG;
		}
		break;
	default:
		break;
	}
}

