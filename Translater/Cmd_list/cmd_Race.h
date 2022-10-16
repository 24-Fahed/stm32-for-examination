#ifndef __CMD_RACE_H__
#define __CMD_RACE_H__

#include "race_counter.h"
#include "cmd_list.h"

static inline void cmd_race_cmdMode(char *mode) {
    counter_main(1);
}

#endif // __CMD_RACE_H__
