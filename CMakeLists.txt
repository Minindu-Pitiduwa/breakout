cmake_minimum_required(VERSION 3.28)
project(Breakout LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(breakout src/main.cpp)
target_compile_features(breakout PRIVATE cxx_std_17)
target_link_libraries(breakout PRIVATE SFML::Graphics)