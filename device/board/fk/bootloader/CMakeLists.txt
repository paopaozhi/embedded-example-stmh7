project(bootloader)

set(SOC_ST_PATH "${CMAKE_SOURCE_DIR}/device/soc/st/STM32CubeH7")
set(SOC_DRIVERS_CMSIS_PATH ${SOC_ST_PATH}/Drivers/CMSIS)
set(SOC_DRIVERS_STMH7_PATH ${SOC_ST_PATH}/Drivers/STM32H7xx_HAL_Driver)


message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

add_executable(${PROJECT_NAME})

# target_link_options(${PROJECT_NAME}
#     PRIVATE 
#         -T \"${CMAKE_SOURCE_DIR}/STM32H7B0VBTx_FLASH.ld\"
# )

message("CMAKE_C_LINK_FLAGS: ${CMAKE_C_LINK_FLAGS}")


target_compile_definitions(${PROJECT_NAME} PRIVATE 
	USE_HAL_DRIVER 
	STM32H7B0xx
)

target_include_directories(${PROJECT_NAME} PRIVATE
    inc

    ${SOC_DRIVERS_CMSIS_PATH}/Include
    ${SOC_DRIVERS_CMSIS_PATH}/Device/ST/STM32H7xx/Include
    ${SOC_DRIVERS_STMH7_PATH}/Inc
    ${SOC_DRIVERS_STMH7_PATH}/Inc/Legacy
)

file(GLOB_RECURSE SRC_SOURCE "src/*.*")

target_sources(${PROJECT_NAME} PRIVATE
    startup_stm32h7b0xx.s
    ${SRC_SOURCE}
    
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_cortex.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_rcc.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_rcc_ex.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_flash.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_flash_ex.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_gpio.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_hsem.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_dma.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_dma_ex.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_mdma.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_pwr.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_pwr_ex.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_i2c.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_i2c_ex.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_exti.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_tim.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_tim_ex.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_uart.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_uart_ex.c
    ${SOC_DRIVERS_STMH7_PATH}/Src/stm32h7xx_hal_ospi.c
)

