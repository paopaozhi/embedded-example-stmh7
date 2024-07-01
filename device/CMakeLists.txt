project(device)

add_library(${PROJECT_NAME} INTERFACE)

enable_language(C ASM)

target_compile_definitions(${PROJECT_NAME} INTERFACE
    USE_HAL_DRIVER
    STM32H7B0xx
)

file(GLOB_RECURSE SOURCES_DRIVER "stm32h7xx_hal_driver/*.c")
file(GLOB_RECURSE REMOVE_SOURCES_DRIVER "stm32h7xx_hal_driver/*_template.c")

list(REMOVE_ITEM SOURCES_DRIVER ${REMOVE_SOURCES_DRIVER})
file(GLOB_RECURSE SOURCES_CUBX "cubx/Core/*.*")

target_include_directories(${PROJECT_NAME} INTERFACE
    cubx/Core/Inc
    CMSIS_5/CMSIS/Core/Include
    cmsis_device_h7/Include
    stm32h7xx_hal_driver/inc/Legacy
    stm32h7xx_hal_driver/inc
)

target_sources(${PROJECT_NAME} INTERFACE
    ${SOURCES_CUBX}
    ${SOURCES_DRIVER}
    cmsis_device_h7/Source/Templates/gcc/startup_stm32h7b0xx.s
)
