
cmake_minimum_required(VERSION 3.10)

project(pwg VERSION 0.1.0 LANGUAGES CXX)

# For C++ projects
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/version.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/version.h"
    @ONLY
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

include_directories(src resources)

file(GLOB SOURCES
    src/main.cpp
    src/diceware_generator.cpp
    src/diceware_lookup.cpp
    src/generator.cpp
    resources/diceware_wordlist.cpp
    resources/diceware_eff_wordlist.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

