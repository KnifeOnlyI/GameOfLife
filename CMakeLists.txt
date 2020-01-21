cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME GameOfLife)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

project(${PROJECT_NAME})

file(
    GLOB_RECURSE
    SOURCES
    ${CMAKE_SOURCE_DIR}/core/source/*.c
    ${CMAKE_SOURCE_DIR}/core/source/*.cpp
)

file(
    GLOB_RECURSE
    HEADERS
    ${CMAKE_SOURCE_DIR}/core/header/*.h
    ${CMAKE_SOURCE_DIR}/core/header/*.hpp
    ${CMAKE_SOURCE_DIR}/core/header/*.inl
)

if (SFML_DIR)
    find_package(SFML REQUIRED)
else ()
    set(SFML_SYSTEM sfml-system)
    set(SFML_WINDOW sfml-window)
    set(SFML_GRAPHICS sfml-graphics)
endif ()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

include_directories(${CMAKE_SOURCE_DIR}/core/header)
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME} ${SFML_SYSTEM} ${SFML_WINDOW} ${SFML_GRAPHICS})