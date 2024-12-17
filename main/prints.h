#ifndef PRINTS_H
#define PRINTS_H
#include <stdio.h>


const char* red = "\033[0;31m";
const char* green = "\033[0;32m";
const char* yellow = "\033[0;33m";
const char* blue = "\033[0;34m";
const char* magenta = "\033[0;35m";
const char* cyan = "\033[0;36m";

const char* reset = "\033[0m";

#define PRINTFL(format, ...)printf("%s" ":" "%d " format, __FILE__, __LINE__, ##__VA_ARGS__)     //wtf, kan makron ta argument?


#define PRINTFC(color, format, ...)printf("%s" format "%s", color, ##__VA_ARGS__,reset)     //wtf, kan makron ta argument?
#define PRINTFC_TASK_1(format, ...) \ 
    PRINTFC(red, "TASK 1: "); \
    printf(format, ##__VA_ARGS__)

#define PRINTFC_TASK_2(format, ...) \ 
    PRINTFC(blue, "TASK 2: "); \
    printf(format, ##__VA_ARGS__)


#define PRINTFC_TASK_3(format, ...) \ 
    PRINTFC(yellow, "TASK 3: "); \
    printf(format, ##__VA_ARGS__)

#define PRINTFC_TASK_4(format, ...) \ 
    PRINTFC(cyan, "TASK 4: "); \
    printf(format, ##__VA_ARGS__)

#define PRINTFC_TASK_5(format, ...) \ 
    PRINTFC(green, "TASK 5: "); \
    printf(format, ##__VA_ARGS__)



#endif