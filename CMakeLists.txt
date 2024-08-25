cmake_minimum_required(VERSION 3.10)
project(Baghchal)

set(CMAKE_CXX_STANDARD 17)

# Path to SFML
set(SFML_DIR "C:\SFML-2.6.1\bin")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(Baghchal main.cpp)
target_link_libraries(Baghchal sfml-system sfml-window sfml-graphics)
