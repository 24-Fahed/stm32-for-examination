#ifndef __TIMER_H__
#define __TIMER_H__

#include "stdio.h"
#include "break_service_Timer.h"

#define BUTTON1_DOWN_STARE      button1_mem != button1_now && button1_now == 1

enum {
    _wait,
    _start,
    _exit,
    _api,
    _api_wait
};

void timer_start(void);
void API_timer_TimerCounter(int *timer_list);
int API_timer_number_counter(int time);

#endif // __TIMER_H__
