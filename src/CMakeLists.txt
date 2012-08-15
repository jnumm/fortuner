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

find_package (GTK2)
find_package (Libnotify)

include_directories (
  ${PROJECT_BINARY_DIR}
  ${GTK2_INCLUDE_DIRS}
  ${LIBNOTIFY_INCLUDE_DIRS}
)
link_directories (${GTK2_LIBRARY_DIRS} ${LIBNOTIFY_LIBRARY_DIRS})
add_executable (${PROJECT_NAME} ${fortuner_SRCS})
add_definitions (${GTK2_CFLAGS_OTHER} ${LIBNOTIFY_CFLAGS_OTHER})
target_link_libraries (
  ${PROJECT_NAME}
  ${GTK2_LIBRARIES}
  ${LIBNOTIFY_LIBRARIES}
)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

if (USE_GAMES_DIR)
  install (TARGETS ${PROJECT_NAME} DESTINATION games)
else()
  install (TARGETS ${PROJECT_NAME} DESTINATION bin)
endif()
