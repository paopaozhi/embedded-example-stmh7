project(drivers_hdm)

add_library(${PROJECT_NAME})

file(GLOB CORE_SRC "core/*.*")

set(ADAPT_PATH "${CMAKE_SOURCE_DIR}/device/board/fk/drivers_adapt")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(${ADAPT_PATH} drivers_adapt)

target_link_libraries(${PROJECT_NAME}
    drivers_adapt
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CORE_SRC}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    interfaces
    # core/include
    core/inner_api
)