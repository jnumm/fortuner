cmake_minimum_required (VERSION 2.8)

project (fortuner)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 3)
set (VERSION_MICRO 1)
set (VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO}")

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${PROJECT_SOURCE_DIR}/cmake/modules/")

install (FILES README DESTINATION share/doc/${PROJECT_NAME})
file (GLOB icons "icons/*")
install (DIRECTORY ${icons} DESTINATION share/icons/hicolor)
install (FILES misc/fortuner.desktop DESTINATION share/applications)
install (FILES doc/fortuner.6 DESTINATION share/man/man6)

option (
  USE_GAMES_DIR
  "Use games/ directory instead of bin/ for binary installation directory."
  OFF
)

option (
  USE_GTK2
  "Use GTK+ 2 libraries and headers."
  OFF
)

option (
  USE_GTK3
  "Use GTK+ 3 libraries and headers."
  ON
)

# Ensure that at least one of them is selected.
if (USE_GTK2)
  set (USE_GTK3 OFF)
endif()

if ((USE_GTK2 AND USE_GTK3) OR (NOT USE_GTK2 AND NOT USE_GTK3))
  message (FATAL_ERROR "Please select either GTK+ 2 or GTK+ 3.")
endif()

add_subdirectory (src)
