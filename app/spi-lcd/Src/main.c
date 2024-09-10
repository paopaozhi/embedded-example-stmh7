#include <FreeRTOS.h>
#include <stdio.h>
#include "cmsis_os2.h"
#include "hdm.h"
#include "lvgl.h"
#include "lv_port_disp.h"

#define UART1 1

osTimerId_t timer_id;

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

void lv_example_button_1(void)
{
    lv_obj_t * label;

    lv_obj_t * btn1 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);
    lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);

    lv_obj_t * btn2 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn2, LV_SIZE_CONTENT);

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Toggle");
    lv_obj_center(label);

}

void timer_hander(void* arg)
{
    lv_tick_inc(1);
}

void app_main(void* arg)
{
    (void)arg;

    IoTUartInit(UART1, NULL);
    IoTUartWrite(UART1, "Hello World\n", 12);

    lv_init();
    lv_port_disp_init();

    timer_id = osTimerNew(timer_hander, osTimerPeriodic,NULL,NULL);
    osTimerStart(timer_id, 1);

    // SPI_LCD_Init();
    // LCD_Clear();
    // LCD_DisplayText(0, 0, "Hello World!");

    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    // lv_obj_t* label = lv_label_create(lv_screen_active());
    // lv_label_set_text(label, "Hello LVGL");
    //
    // lv_obj_set_style_text_align(label,LV_TEXT_ALIGN_CENTER,LV_PART_MAIN);
    // lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_example_button_1();

    while (1)
    {
        lv_task_handler();
        osDelay(5);
    }
}
