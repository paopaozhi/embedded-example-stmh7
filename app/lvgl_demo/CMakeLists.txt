project(lvgl_demo)

set(THRID_PARTY_PATH "${CMAKE_SOURCE_DIR}/third_party")
set(RTOS_PATH "${CMAKE_SOURCE_DIR}/device/board/fk/Middlewares/Third_Party/FreeRTOS/")
set(DRIVERS_HDM_PATH "${CMAKE_SOURCE_DIR}/drivers/hdm")

add_library(${PROJECT_NAME} INTERFACE)

file(GLOB_RECURSE SOURCE "src/*.c")

target_sources(${PROJECT_NAME} INTERFACE
    ${SOURCE}
)
target_include_directories(${PROJECT_NAME} INTERFACE
    Inc
)