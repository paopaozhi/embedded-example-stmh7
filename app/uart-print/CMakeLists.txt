project(uart-print)

add_library(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES "src/*.c")

set(RTOS_PATH "${CMAKE_SOURCE_DIR}/device/board/fk/Middlewares/Third_Party/FreeRTOS/")
set(DRIVERS_HDM_PATH "${CMAKE_SOURCE_DIR}/drivers/hdm")

target_sources(${PROJECT_NAME} PRIVATE
    src/main.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${RTOS_PATH}/Source/include
    ${RTOS_PATH}/Source/CMSIS_RTOS_V2
    ${RTOS_PATH}/Source/portable/GCC/ARM_CM4F

    # ${DRIVERS_HDM_PATH}/interfaces
)

target_link_libraries(${PROJECT_NAME}
    drivers_hdm
)