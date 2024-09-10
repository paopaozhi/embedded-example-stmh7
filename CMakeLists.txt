cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Image)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

target_link_options(${PROJECT_NAME}
    PRIVATE 
        -T "${CMAKE_SOURCE_DIR}/device/board/fk/STM32H7B0VBTx_FLASH.ld"
        "-Wl,-Map=${CMAKE_PROJECT_NAME}.map"
)

# Add STM32CubeMX generated sources
add_subdirectory(device/board/fk)
add_subdirectory(drivers)
add_subdirectory(app)

add_subdirectory(third_party/lvgl)

set(RTOS_PATH "${CMAKE_SOURCE_DIR}/device/board/fk/Middlewares/Third_Party/FreeRTOS")

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
    LV_CONF_INCLUDE_SIMPLE
)

target_include_directories(lvgl PUBLIC
    app/spi-lcd/Inc
    device/board/fk/Core/Inc
    ${RTOS_PATH}/Source/include
    ${RTOS_PATH}/Source/CMSIS_RTOS_V2
    ${RTOS_PATH}/Source/portable/GCC/ARM_CM4F
)


# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    fk_h7b0 
    # Add user defined libraries
    drivers
    app
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    lvgl::lvgl
)


add_subdirectory(device/board/fk/bootloader)