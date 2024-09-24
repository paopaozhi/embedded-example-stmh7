project(app)

add_library(${PROJECT_NAME} INTERFACE)

# add_subdirectory(uart-print)
add_subdirectory(lvgl_demo)

target_link_libraries(${PROJECT_NAME} INTERFACE
    # uart-print
    lvgl_demo
)
