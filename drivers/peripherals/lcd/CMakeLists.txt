project(peripherals-lcd)

add_library(${PROJECT_NAME} INTERFACE)

file(GLOB_RECURSE SOURCE "src/*.c")

target_sources(${PROJECT_NAME} INTERFACE
    ${SOURCE}
)

target_include_directories(${PROJECT_NAME} INTERFACE
    include
)