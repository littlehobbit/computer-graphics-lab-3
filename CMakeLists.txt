cmake_minimum_required(VERSION 3.10)

project(lab-3)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/filler.cpp
    src/line_drawlers.cpp
    src/triangle.cpp
    src/minimap.cpp
)

add_subdirectory(libs)

target_link_libraries(
    ${PROJECT_NAME}
    sfml-graphics    
    sfml-window    
    CLI11::CLI11
)