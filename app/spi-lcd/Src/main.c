#include <FreeRTOS.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"
#include "hdm.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lcd_spi_200.h"
#include "demos/lv_demos.h"
// #include "lv_demos.h"

#define UART1 1

osTimerId_t timer_id;

void lv_example_button_1(void)
{
    lv_obj_t *btn = lv_btn_create(lv_scr_act()); /*Add a button to the current screen*/
    lv_obj_set_pos(btn, 10, 10);                 /*Set its position*/
    lv_obj_set_size(btn, 100, 50);               /*Set its size*/
    lv_obj_center(btn);                          /*Align to the center*/
    // lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL); /*Assign a callback to the button*/

    lv_obj_t *label = lv_label_create(btn); /*Add a label to the button*/
    lv_label_set_text(label, "Button");     /*Set the labels text*/
    lv_obj_center(label);                   /*Align the label to the center*/
}

void timer_hander(void *arg)
{
    (void)arg;
    lv_tick_inc(1);
}

void app_main(void *arg)
{
    (void)arg;

    IoTUartInit(UART1, NULL);
    IoTUartWrite(UART1, (uint8_t *)"Hello World\n", 12);

    lv_init();
    lv_port_disp_init();
    lv_tick_set_cb(xTaskGetTickCount);

    // timer_id = osTimerNew(timer_hander, osTimerPeriodic, NULL, NULL);
    // osTimerStart(timer_id, 1);

    // SPI_LCD_Init();
    // LCD_Clear();
    // LCD_DisplayText(0, 0, "Hello World!");

    // lv_example_button_1();
    lv_demo_benchmark();

    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        osDelay(time_till_next);
    }
}
