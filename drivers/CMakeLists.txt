project(drivers)

add_library(${PROJECT_NAME} INTERFACE)

add_subdirectory(hdm)
add_subdirectory(peripherals/lcd)

target_link_libraries(${PROJECT_NAME} INTERFACE
    drivers_hdm
    peripherals-lcd
)
