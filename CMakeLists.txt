cmake_minimum_required (VERSION 2.6)

project (fortuner)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 3)
set (VERSION_MICRO 1)
set (VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${PROJECT_SOURCE_DIR}/cmake/modules/")

install (FILES README DESTINATION share/doc/${PROJECT_NAME})
file (GLOB icons "icons/*")
install (DIRECTORY ${icons} DESTINATION share/icons/hicolor)
install (FILES misc/fortuner.desktop DESTINATION share/applications)
install (FILES doc/fortuner.6 DESTINATION share/man/man6)

add_subdirectory (src)
