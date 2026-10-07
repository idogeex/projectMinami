cmake_minimum_required(VERSION 3.20)

project(ProjectMinami LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ProjectMinami
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
)

target_include_directories(ProjectMinami PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_directories(ProjectMinami PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/SDL3
)

target_link_libraries(ProjectMinami PRIVATE
    SDL3
)

add_custom_command(TARGET ProjectMinami POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/dll/SDL3.dll"
        "$<TARGET_FILE_DIR:ProjectMinami>"
)