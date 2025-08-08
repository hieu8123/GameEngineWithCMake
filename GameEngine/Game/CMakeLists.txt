project(Game VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE VIEngine)
# Game needs only its own source includes; the engine publishes its includes via target_include_directories(PUBLIC)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)