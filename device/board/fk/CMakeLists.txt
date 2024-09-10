# Set the project name
set(CMAKE_PROJECT_NAME fk_h7b0)

# Core project settings
project(${CMAKE_PROJECT_NAME})

# Create an executable object type
add_library(${CMAKE_PROJECT_NAME} INTERFACE)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} INTERFACE
    stm32cubemx
)
