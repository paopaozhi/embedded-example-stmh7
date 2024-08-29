#ifndef __HDM_H
#define __HDM_H

#include "hdm_config.h"

#ifdef GPIO
#include "iot_gpio.h"
#endif

#ifdef UART
#include "iot_uart.h"
#endif

#ifdef IIC
#include "iot_i2c.h"
#endif
 
#endif
