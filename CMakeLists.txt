
cmake_minimum_required(VERSION 3.10)

project(pwg VERSION 0.1.0 LANGUAGES CXX)

# For C++ projects
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

include_directories(src resources)

file(GLOB SOURCES 
    src/main.cpp
    src/diceware.cpp
    src/generator.cpp
    resources/diceware_wordlist.cpp
    resources/diceware_eff_wordlist.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

