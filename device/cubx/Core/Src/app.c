// #include <stdio.h>
// #include <string.h>

// #include "main.h"
// #include "stdio.h"

// extern UART_HandleTypeDef huart1;

// void app(void) {
//   // memset(mpudata, 0, sizeof(mpudata));
//   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,GPIO_PIN_RESET);
//   printf("Hello World!\r\n");

//   HAL_UART_Transmit(&huart1, (uint8_t *)"123\n", 4, 0xFFFF);

//   __HAL_RCC_GPIOC_CLK_ENABLE();

//   GPIO_InitTypeDef gpio_init;

//   gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
//   gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//   gpio_init.Pin = GPIO_PIN_1;
//   gpio_init.Pull = GPIO_PULLUP;

//   HAL_GPIO_Init(GPIOC, &gpio_init);
//   while (1) {
//     /* code */
//     HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);
//     HAL_Delay(500);
//   }

//   return;
// }

// int __io_putchar(int ch) {
//   HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
//   // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);
//   return ch;
// }
