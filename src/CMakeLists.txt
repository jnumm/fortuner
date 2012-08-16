cmake_minimum_required (VERSION 2.8)

project (fortuner)

set (fortuner_SRCS
  gtk_ui.cpp
  main.cpp
  settings.cpp
)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

if (USE_GTK2)
  find_package (GTK2)
  set (SELECTED_GTK_INCLUDE_DIRS ${GTK2_INCLUDE_DIRS})
  set (SELECTED_GTK_LIBRARY_DIRS ${GTK2_LIBRARY_DIRS})
  set (SELECTED_GTK_CFLAGS_OTHER ${GTK2_CFLAGS_OTHER})
elseif (USE_GTK3)
  find_package (PkgConfig REQUIRED)
  pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
  set (SELECTED_GTK_INCLUDE_DIRS ${GTK3_INCLUDE_DIRS})
  set (SELECTED_GTK_LIBRARY_DIRS ${GTK3_LIBRARY_DIRS})
  set (SELECTED_GTK_CFLAGS_OTHER ${GTK3_CFLAGS_OTHER})
endif ()

find_package (Libnotify)

include_directories (
  ${PROJECT_BINARY_DIR}
  ${SELECTED_GTK_INCLUDE_DIRS}
  ${LIBNOTIFY_INCLUDE_DIRS}
)
link_directories (${SELECTED_GTK_LIBRARY_DIRS} ${LIBNOTIFY_LIBRARY_DIRS})
add_executable (${PROJECT_NAME} ${fortuner_SRCS})
add_definitions (${SELECTED_GTK_CFLAGS_OTHER} ${LIBNOTIFY_CFLAGS_OTHER})
target_link_libraries (
  ${PROJECT_NAME}
  ${SELECTED_GTK_LIBRARIES}
  ${LIBNOTIFY_LIBRARIES}
)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

if (USE_GAMES_DIR)
  install (TARGETS ${PROJECT_NAME} DESTINATION games)
else()
  install (TARGETS ${PROJECT_NAME} DESTINATION bin)
endif()
