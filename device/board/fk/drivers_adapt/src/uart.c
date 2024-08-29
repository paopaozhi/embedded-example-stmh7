#include <stdio.h>
#include "iot_uart.h"
#include "stm32h7xx_hal.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "cmsis_os2.h"

typedef enum
{
    uart1 = 0,
    uart2,
} UartId_TypeDef;

typedef struct
{
    uint8_t buf[128];
    uint8_t buf_len;
    uint8_t state;

    xTimerHandle receive_timerHandle;

    osEventFlagsId_t readOk_Event;
} Uart_TypeDef;

#define UART_RECEIVE_OK 0x00000001U
#define UART_COPY_OK 0x00000002U

const osThreadAttr_t usart_task_attr = {
    .name = "usart_task",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 256 * 4};

static uint8_t UartId = 0xff;

static osSemaphoreId_t read_Sema;

static Uart_TypeDef uartList[3];

extern UART_HandleTypeDef huart1;

void usart_task(void *argument);

/**
 * @brief 串口接收完成（超时）软件定时器回调函数
 *
 * @param xTimer
 */
static void uartReceiveHandle(TimerHandle_t xTimer)
{
    osEventFlagsSet(uartList[UartId].readOk_Event, UART_RECEIVE_OK);
}

/**
 * @brief 串口接收完成（超时）软件定时器初始化
 *
 * @param uart
 */
static void uart_new_timer(Uart_TypeDef *uart)
{
    uart->receive_timerHandle = xTimerCreate(NULL, 5, pdFALSE, (void *)0, uartReceiveHandle);
    if (uart->receive_timerHandle == NULL)
    {
        Error_Handler();
    }
    xTimerStop(uart->receive_timerHandle, portMAX_DELAY);
}

/**
 * @brief 串口设备必要资源初始化
 *        该函数需要在RTOS内核启动前调用
 *        注意：与设备无关，与RTOS强相关！！
 *
 */
static void prvUart_Init(void)
{
    Uart_TypeDef *pUart;
    uint8_t uart_id_len = sizeof(uartList) / sizeof(Uart_TypeDef) - 1;

    osThreadNew(usart_task, NULL, &usart_task_attr);
    read_Sema = osSemaphoreNew(1, 0, NULL);

    // 初始化申请的串口资源
    for (int i = 0; i < uart_id_len; i++)
    {
        pUart = &uartList[i];
        uart_new_timer(pUart);

        pUart->readOk_Event = osEventFlagsNew(NULL);

        if (pUart->readOk_Event == NULL)
        {
            board_error_handle();
        }

        pUart->state = 0;
        pUart->buf_len = 0;
        memset(pUart->buf, 0, 128);

        pUart = NULL;
    }
}

/**
 * @brief 串口设备处理线程
 *
 * @param argument
 */
void usart_task(void *argument)
{
    Uart_TypeDef *pUart;

    for (;;)
    {
        osSemaphoreAcquire(read_Sema, osWaitForever);

        pUart = &uartList[UartId];

        switch (UartId)
        {
        case uart1:
            HAL_UART_Receive_IT(&huart1, pUart->buf, 1);
            osEventFlagsWait(pUart->readOk_Event, UART_COPY_OK, osFlagsWaitAny, osWaitForever);

            HAL_UART_Abort_IT(&huart1);
            break;

        default:
            continue;
            break;
        }

        pUart->state = 0;
        pUart->buf_len = 0;
        memset(pUart->buf, 0, 128);
        // UartId = 0xff;
        pUart = NULL;
    }
}

/**
 * @brief 串口接收完成回调函数
 *
 * @param huart 串口句柄
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        Uart_TypeDef *pUart = &uartList[0];
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xTimerStartFromISR(pUart->receive_timerHandle, &xHigherPriorityTaskWoken);
        pUart->state = 1;
        pUart->buf_len++;
        HAL_UART_Receive_IT(huart, (pUart->buf + pUart->buf_len), 1);
    }
    else if (huart->Instance == USART2)
    {
        // BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        // xTimerStartFromISR(usartTimerHandle, &xHigherPriorityTaskWoken);
        // USART1_State = 1;
        // USART1_BufLen++;
        // HAL_UART_Receive_IT(huart, (USART1_Buf + USART1_BufLen), 1);
    }
    else if (huart->Instance == USART3)
    {
        // BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        // xTimerStartFromISR(usartTimerHandle, &xHigherPriorityTaskWoken);
        // USART1_State = 1;
        // USART1_BufLen++;
        // HAL_UART_Receive_IT(huart, (USART1_Buf + USART1_BufLen), 1);
    }
    else
    {
    }
}

// PUBLIC API
unsigned int IoTUartInit(unsigned int id, const IotUartAttribute *param)
{
    switch (id)
    {
    case 1:
        if (uartList != NULL)
        {
            printf("UART1 init OK for STM32Cube\n");
        }
        else
        {
            printf("UART1 init failed\n");
        }
        break;

    default:
        printf("No such UART%d resource\n", id);
        break;
    }
}

int IoTUartWrite(unsigned int id, const unsigned char *data, unsigned int dataLen)
{
    if (id == 1)
    {
        extern UART_HandleTypeDef huart1;
        HAL_UART_Transmit(&huart1, data, dataLen, 0xf);
    }
}

int IoTUartRead(unsigned int id, unsigned char *data, unsigned int dataLen)
{
    if (id <= 3)
    {
        Uart_TypeDef *pUart = &uartList[id];
        UartId = id;
        osEventFlagsId_t pEvent = pUart->readOk_Event;
        uint32_t result;

        osSemaphoreRelease(read_Sema);

        result = osEventFlagsWait(pEvent, UART_RECEIVE_OK, osFlagsWaitAny, osWaitForever);
        if (pUart->buf_len >= 128)
        {
            return -1;
        }
        strncpy((char *)data, (char *)pUart->buf, pUart->buf_len);
        dataLen = pUart->buf_len;
        osEventFlagsSet(pUart->readOk_Event, UART_COPY_OK);
        return 0;
    }
}

int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xff);

    return ch;
}
