project(drivers_adapt)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ./src/uart.c
)

target_link_libraries(${PROJECT_NAME}
    stm32cubemx
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/drivers/hdm/core/inner_api
)

target_include_directories(${PROJECT_NAME} PUBLIC
    .
)