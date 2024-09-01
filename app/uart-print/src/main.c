#include <stdio.h>
#include "cmsis_os2.h"
#include "hdm.h"

#define UART1 1

void app_main(void)
{
    IoTUartInit(UART1, NULL);
    IoTUartWrite(UART1, "Hello World\n", 12);
    osThreadExit();
}
