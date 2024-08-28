#include <stdio.h>
#include "cmsis_os2.h"

void app_main(void)
{
    int i = 100;
    i++;
    osThreadExit();
}
