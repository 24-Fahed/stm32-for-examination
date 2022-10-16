#include "cmd_timer.h"

void cmd_timer_counter(char *time_str) {
    /*
    char tempCall[5];                          // ¼ÇÂ¼Ê±¼ä
    int timer_list[5];
    DataFlow String_list = {'\0', 0, 0, 0};
    
    ustrcpy(time_str, (&(String_list.data)[0]));
    printf("timer_str %s \n", String_list.data);
    
    get_Word(&String_list, &(tempCall[0]));
    printf("get: %s", tempCall);
    timer_list[0] = char_to_int(tempCall);
    printf("%d  ", timer_list[0]);
    
    get_Word(&String_list, &(tempCall[0]));
    timer_list[1] = char_to_int(tempCall);
    printf("%d  ", timer_list[1]);
    
    get_Word(&String_list, &(tempCall[0]));
    timer_list[2] = char_to_int(tempCall);
    printf("%d  ", timer_list[2]);
    
    get_Word(&String_list, &(tempCall[0]));
    timer_list[3] = char_to_int(tempCall);
    printf("%d  ", timer_list[3]);
    
    get_Word(&String_list, &(tempCall[0]));
    timer_list[4] = char_to_int(tempCall);
    printf("%d  \n", timer_list[4]);
    */
    printf("counter ready \n");
    int timer_table[] = {12, 14, 16, 18, 20};
    API_timer_TimerCounter(timer_table);
}
