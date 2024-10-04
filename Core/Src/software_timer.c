/*
 * software_timer.c
 *
 *  Created on: Oct 4, 2024
 *      Author: DELL
 */

#include "software_timer.h"

int timer_counter[NUM_TIM];
int timer_flag[NUM_TIM];

void setTimer(int index, int counter)
{
	if (index < NUM_TIM)
	{
		timer_flag[index] = 0;
		timer_counter[index] = counter / TICK;
	}
}

void clearTimer(int index)
{
	if (index < NUM_TIM)
	{
		timer_flag[index] = 0;
		timer_counter[index] = 0;
	}
}

void timerRun()
{	// needed to optimize this to O(1)
    for (int i = 0; i < NUM_TIM; i++)
    {
        if (timer_counter[i] >= 0)
        {
            timer_counter[i] --;
            if (timer_counter[i] <= 0)
            {
                timer_flag[i] = 1;
            }
        }
    }
}

int getTimerFlag(int index)
{
	if (index < NUM_TIM)
	{
		return timer_flag[index];
	}

	return -1;	// Error
}

