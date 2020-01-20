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

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)