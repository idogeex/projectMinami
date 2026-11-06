cmake_minimum_required(VERSION 3.20)

project(ProjectMinami LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ProjectMinami
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Grid.cpp
    src/MazeGenerator.cpp
    src/Hud.cpp
    src/Pathfinding.cpp
)

target_include_directories(ProjectMinami PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_directories(ProjectMinami PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/SDL3
    ${CMAKE_SOURCE_DIR}/lib/SDL3_ttf
)

target_link_libraries(ProjectMinami PRIVATE
    SDL3
    SDL3_ttf
)

target_compile_options(ProjectMinami PRIVATE -Wall -Wextra)
target_link_options(ProjectMinami PRIVATE -static-libgcc -static-libstdc++)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(ProjectMinami PROPERTIES WIN32_EXECUTABLE ON)
endif()

add_custom_command(TARGET ProjectMinami POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/dll/SDL3.dll"
        "${CMAKE_SOURCE_DIR}/dll/SDL3_ttf.dll"
        "$<TARGET_FILE_DIR:ProjectMinami>"
)