cmake_minimum_required (VERSION 2.6)

project (fortuner)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)
set (VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${PROJECT_SOURCE_DIR}/cmake/modules/")

add_subdirectory (src)
