cmake_minimum_required (VERSION 2.8)

project (fortuner)

set (fortuner_SRCS
  main.cpp
  gtk_ui.cpp
)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

find_package (GTK2)
find_package (Libnotify)

include_directories (${GTK2_INCLUDE_DIRS} ${LIBNOTIFY_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS} ${LIBNOTIFY_LIBRARY_DIRS})
add_executable (${PROJECT_NAME} ${fortuner_SRCS})
add_definitions (${GTK2_CFLAGS_OTHER} ${LIBNOTIFY_CFLAGS_OTHER})
target_link_libraries (
  ${PROJECT_NAME}
  ${GTK2_LIBRARIES}
  ${LIBNOTIFY_LIBRARIES}
)

install (TARGETS ${PROJECT_NAME} DESTINATION bin)
