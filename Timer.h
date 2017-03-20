#ifndef __TIMER_H
#define __TIMER_H

// Variables
extern unsigned int msCounter;
extern unsigned int csCounter;
extern unsigned int secCounter;

// Function declarations
void InitTimer0(void);
void Init1msecTimerInterrupt(void);
void UpdateTimeCounters(unsigned char);

#endif