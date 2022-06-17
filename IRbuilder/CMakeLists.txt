CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

add_definitions(-DFULL_IMPL)

project(IRBuilder)
SET (CMAKE_CXX_STANDARD 14)

SET (CMAKE_BUILD_TYPE "Debug")
SET (c1recognizer_DIR "${CMAKE_SOURCE_DIR}/../c1recognizer/bin/cmake")
SET (irbackend_DIR "${CMAKE_SOURCE_DIR}/../irbackend/bin/cmake")
find_package(c1recognizer)
include_directories(${C1RECOGNIZER_INCLUDE_DIRS})
link_directories(${C1RECOGNIZER_LIBRARY_DIRS})

find_package(irbackend)
include_directories(${IRBACKEND_INCLUDE_DIRS})
link_directories(${IRBACKEND_LIBRARY_DIRS})
message(STATUS "Found irbackend ${IRBACKEND_INCLUDE_DIRS}")


include_directories(dependency/c1recognizer/include)
include_directories(dependency/irbackend/include/irbackend)
include_directories(dependency/irbackend/include/codegen)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
