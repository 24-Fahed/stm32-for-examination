#ifndef __CMD_TIMER_H__
#define __CMD_TIMER_H__

#include "timer.h"
#include "stdio_user.h"

static inline void cmd_timer_sec(char *test) {
    timer_start();
}

void cmd_timer_counter(char *time_str);

#endif // __CMD_TIMER_H__
