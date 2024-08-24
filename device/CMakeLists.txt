project(device)

add_library(${PROJECT_NAME} INTERFACE)

enable_language(C ASM)

add_subdirectory(cubx/cmake/stm32cubemx)

target_link_directories(${CMAKE_PROJECT_NAME} INTERFACE
    # Add user defined library search paths
    stm32cubemx
)
