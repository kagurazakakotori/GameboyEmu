cmake_minimum_required(VERSION 3.0)
project(GameboyEmu)
set(EXECUTABLE_NAME "GameboyEmu")

aux_source_directory(./source source_list)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_BUILD 0)

configure_file(
    "source/version.h.in"
    "source/version.h"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
include_directories("${CMAKE_SOURCE_DIR}/include/termcolor")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(SFML_STATIC_LIBRARIES true)
else()
  set(SFML_STATIC_LIBRARIES false)
endif()

find_package(SFML 2 REQUIRED graphics window system)
include_directories(${SFML_INCLUDE_DIR})

add_executable(${EXECUTABLE_NAME} ${source_list})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})