cmake_minimum_required (VERSION 2.6)

project (fortuner)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)
set (VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${PROJECT_SOURCE_DIR}/cmake/modules/")

install (FILES README DESTINATION share/doc/${PROJECT_NAME})
file (GLOB icons "icons/*")
install (DIRECTORY ${icons} DESTINATION share/icons/hicolor)

add_subdirectory (src)
