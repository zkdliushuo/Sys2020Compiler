cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(YAL)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

file(GLOB ALLHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/irbackend/*.h)
file(GLOB ALLHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen/*.h)

# include 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/irbackend)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/codegen)

# add generated grammar to c1_recognizer binary target
file(GLOB ALLSRCS1 ${PROJECT_SOURCE_DIR}/src/irbackend/*.cpp)
file(GLOB ALLSRCS2 ${PROJECT_SOURCE_DIR}/src/codegen/*.cpp)

add_library(irbackend ${ALLSRCS1} ${ALLSRCS2})

add_executable(sysyvm_test test/main.cpp ${ALLSRCS} ${ALLHEADERS})
add_dependencies(sysyvm_test irbackend)
target_link_libraries(sysyvm_test irbackend)

install(
  TARGETS irbackend
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(DIRECTORY include/irbackend/ include/codegen/ DESTINATION include/irbackend)

configure_file(irbackend-config.cmake.in irbackend-config.cmake @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/irbackend-config.cmake DESTINATION cmake)
